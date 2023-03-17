#include "KeyExplanationScene.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "KeyGameOverScene.h"
#include <time.h>		// ランダム用
#include "DxLib.h"

void TitleScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc = &TitleScene::NormalUpdate;
		fadeValue = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	// 次へボタンが押されたら次のシーンへ移行する
	if (input.IsTriggred(InputType::next))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &TitleScene::FadeOutUpdate;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyExplanationScene(manager_));
		return;
	}
}

void TitleScene::StarAnimation()
{
	// ランダムに星のアニメーションを描画
	switch (starNum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
						  indexX * posX, indexY * posY,
						  indexX, indexY,
						  1, 0, starHandle1,
						  true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
						  indexX * posX, indexY * posY,
						  indexX, indexY,
						  1, 0, starHandle2,
						  true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
						  indexX * posX, indexY * posY,
						  indexX, indexY,
						  1, 0, starHandle3,
						  true, false);
		break;
	}

	frameCount++;

	if (frameCount > 2)	// 2フレームごとに画像を右に192移動させる
	{
		frameCount = 0;	// フレームカウントをリセット
		posX++;	//1をプラスする
	}
	if (posX >= 5)	// 画像の右まで移動すると左に戻す
	{
		posX = 0;	// 0に戻す
		posY += 1;	// アニメーションを一段下げる

	}
	if (posY >= 4)	// 一番最後の段より大きくなろうとしたら
	{
		posY = 0;	// ゼロに戻す

		// 一番最後まで行ったら場所をランダムで生成する
		srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
		starNum = rand() % starRandomNum + 1;		// 1～3の乱数を出す
		starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
		starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)
	}
}

void TitleScene::CatAnimation()
{
	// ランダムに猫のアニメーションを描画
	switch (catNum)
	{
	case 1:
		DrawRectRotaGraph(catX, catY,//表示したい座標の指定
			32 * animationNumber,
			32 + (32 * imgidx),		//切り取り左上(+32は上のよくわかんないやつを省いてる）
			32, 32,					//幅、高さ（画像の大きさ32）
			4.0f, 0.0f,				//拡大率、回転角度
			catHandle1, true);
		break;

	case 2:
		DrawRectRotaGraph(catX, catY,//表示したい座標の指定
			32 * animationNumber,
			32 + (32 * imgidx),		//切り取り左上(+32は上のよくわかんないやつを省いてる）
			32, 32,					//幅、高さ（画像の大きさ32）
			4.0f, 0.0f,				//拡大率、回転角度
			catHandle2, true);
		break;

	case 3:
		DrawRectRotaGraph(catX, catY,//表示したい座標の指定
			32 * animationNumber,
			32 + (32 * imgidx),		//切り取り左上(+32は上のよくわかんないやつを省いてる）
			32, 32,					//幅、高さ（画像の大きさ32）
			4.0f, 0.0f,				//拡大率、回転角度
			catHandle3, true);
		break;
	}

	//アニメーションが最後まで行ったら16に戻してあげる
	if (animationNumber > 19)
	{
		animationNumber = 16;
	}

	timer++;        //時間のカウント
	
	if (timer >= 16)
	{
		//インターバルより大きくなったらアニメーションを動かす
		animationNumber++;
		
		catX -= 30;

		if (0 > catX)	// 猫が左から出そうになったら右から再度表示する
		{
			// 一番最後まで行ったら場所をランダムで生成する　
			srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
			catNum = rand() % catRandomNum + 1;		// 1～3の乱数を出す

			catX = 1632;	// 自然に入れ替われるように画面外(xが1632)の位置から描画
		}
		
		timer = 0;
	}
	
	// ハンドルがランダムになっているかを確認するための表示(デバック用)
//	SetFontSize(30);
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "猫ハンドル番号:%d", catNum);
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
updateFunc(&TitleScene::FadeInUpdate)
{
	// 画像のロード
	titleHandle = LoadGraph("data/TitleBack.png");
	titlerogoHandle = LoadGraph("data/Titlerogo.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");
	
	catHandle1  = LoadGraph("data/cat/calico_0.png");
	catHandle2  = LoadGraph("data/cat/game_boy_1.png");
	catHandle3  = LoadGraph("data/cat/indigo_0.png");
	
	buttonAhandle = LoadGraph("data/button/buttonA.png");

	//初期化
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化

	// 星アニメーションののランダム関係の処理
	starNum = rand() % starRandomNum + 1;		// 1～3の乱数を出す
	starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
	starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)

	// 猫アニメーションのランダム関係の処理
	catNum = rand() % catRandomNum + 1;	// 1～3の乱数を出す

	// BGMの読みこみ
	musicTitle = LoadSoundMem("data/BGM/TitleBGM.mp3");

	// BGMの音量を調整する
	ChangeVolumeSoundMem(255 * 50 / 100, musicTitle);

	// BGMを呼び出す
	PlaySoundMem(musicTitle, DX_PLAYTYPE_LOOP, false);

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

TitleScene::~TitleScene()
{
	// 画像のデリート
	DeleteGraph(titleHandle);
	DeleteGraph(titlerogoHandle);

	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);
	
	DeleteGraph(catHandle1);
	DeleteGraph(catHandle2);
	DeleteGraph(catHandle3);

	DeleteGraph(buttonAhandle);

	// 音楽のデリート
	DeleteSoundMem(musicTitle);
	DeleteSoundMem(seButton);
}

void TitleScene::Update(const InputState& input)
{
	(this ->*updateFunc)(input);
}


void TitleScene::Draw()
{
	// 背景描画
	DrawGraph(0, 0, titleHandle, true);

	// ランダムになっているか(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d\n", starnum);
	// フレーム数(デバック用)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "フレーム:% d\n", frameCount);
	
	StarAnimation();	// 星のアニメーションを呼び出す
	CatAnimation();		// 猫のアニメーションを呼び出す

	DrawGraph(200, 340, titlerogoHandle, true);	// タイトルロゴを描画

	ChangeFont("UD デジタル 教科書体 NK-B");	// UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント

	// 点滅処理
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		DrawGraph(790, 610, buttonAhandle, true);
		SetFontSize(50);
		DrawFormatString(660, 650, GetColor(255, 255, 77), "PUSH");
	}

	// シーン確認用
//	SetFontSize(50);
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトル");

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	
	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
