#include "KeyGameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "KeyField.h"
#include "PadExplanationScene.h"
#include <time.h>		// ランダム用
#include "DxLib.h"

void KeyGameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &KeyGameClearScene::NormalUpdate;
		fadeValue = 0;
	}
}

void KeyGameClearScene::NormalUpdate(const InputState& input)
{
	// タイトルの場合
	if (input.IsTriggred(InputType::title))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seBackButton);

		// SEを呼び出す
		PlaySoundMem(seBackButton, DX_PLAYTYPE_BACK, false);

		manager_.CangeScene(new TitleScene(manager_));
		return;
	}

	// 次の問題に進む場合
	if (input.IsTriggred(InputType::next))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &KeyGameClearScene::FadeOutUpdate;
	}

	// リスタートの場合
	if (input.IsTriggred(InputType::prev))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void KeyGameClearScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval));
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new PadExplanationScene(manager_));
		return;
	}
}

void KeyGameClearScene::StarAnimation()
{
	// ランダムにアニメーションを描画
	switch (starNum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
						  starIndexX * starPosX, starIndexY * starPosY,
						  starIndexX, starIndexY,
						  1, 0, starHandle1,
						  true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
						  starIndexX * starPosX, starIndexY * starPosY,
						  starIndexX, starIndexY,
						  1, 0, starHandle2,
						  true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
						  starIndexX * starPosX, starIndexY * starPosY,
						  starIndexX, starIndexY,
						  1, 0, starHandle3,
						  true, false);
		break;
	}

	frameCount++;

	if (frameCount > 2)	//2フレームごとに画像を右に192移動させる
	{
		frameCount = 0;	// フレームカウントをリセット
		starPosX++;	//1をプラスする
	}
	if (starPosX >= 5)	// 画像の右まで移動すると左に戻す
	{
		starPosX = 0;	//0に戻す
		starPosY += 1;	// アニメーションを一段下げる

	}
	if (starPosY >= 4)	//一番最後の段より大きくなろうとしたら
	{
		starPosY = 0;	//ゼロに戻す

		//一番最後まで行ったら場所をランダムで生成する
		srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
		starNum = rand() % randomNum + 1;		// 1～3の乱数を出す
		starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
		starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)
	}
}

void KeyGameClearScene::HanabiAnimation()
{
	// ランダムで3パターンの花火を表示する
	switch (hanabiNum)
	{
	case 1:
		DrawRectRotaGraph(150, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle1, true);

		DrawRectRotaGraph(1400, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle2, true);

		break;

	case 2:
		DrawRectRotaGraph(150, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle3, true);

		DrawRectRotaGraph(1400, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle5, true);

		break;

	case 3:
		DrawRectRotaGraph(150, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle4, true);

		DrawRectRotaGraph(1400, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle6, true);

		break;
	}

	//アニメーションが最後まで行ったら14に戻してあげる
	if (hanabiAnimationNumber > 14)
	{
		hanabiAnimationNumber = 0;

		// SEの読み込み
		seHanabi = LoadSoundMem("data/BGM/HanabiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 100 / 100, seHanabi);

		// SEを呼び出す
		PlaySoundMem(seHanabi, DX_PLAYTYPE_BACK, false);

		srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
		hanabiNum = rand() % hanabiRandomNum + 1;		// 1～3の乱数を出す		
	}

	timer++;        //時間のカウント

	if (timer >= 5)
	{
		//インターバルより大きくなったらアニメーションを動かす
		hanabiAnimationNumber++;

		timer = 0;
	}

	

	// デバック用
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "何枚目か %d", hanabiNum);
}

KeyGameClearScene::KeyGameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&KeyGameClearScene::FadeInUpdate)
{
	// 画像のロード
	gameClearHandle = LoadGraph("data/ClearBack.png");
	buttonBACKhandle = LoadGraph("data/button/buttonBACK.png");
	buttonAhandle = LoadGraph("data/button/buttonA.png");
	buttonBhandle = LoadGraph("data/button/buttonB.png");

	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");

	hanabiHandle1 = LoadGraph("data/png/hanabi1.png");
	hanabiHandle2 = LoadGraph("data/png/hanabi2.png");
	hanabiHandle3 = LoadGraph("data/png/hanabi3.png");
	hanabiHandle4 = LoadGraph("data/png/hanabi4.png");
	hanabiHandle5 = LoadGraph("data/png/hanabi5.png");
	hanabiHandle6 = LoadGraph("data/png/hanabi6.png");

	//初期化
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	starNum = rand() % randomNum + 1;		// 1～3の乱数を出す
	starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
	starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)

	hanabiNum = rand() % hanabiRandomNum + 1;	// 1～3の乱数を出す

	// BGMの読みこみ
	musicClear = LoadSoundMem("data/BGM/GameClearBGM.mp3");

	// BGMの音量を調整する
	ChangeVolumeSoundMem(255 * 50 / 100, musicClear);

	// BGMを呼び出す
	PlaySoundMem(musicClear, DX_PLAYTYPE_LOOP, false);

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");

	// SEの読み込み
	seBackButton = LoadSoundMem("data/BGM/BackTitleSE.mp3");

}

KeyGameClearScene::~KeyGameClearScene()
{
	// 画像のデリート
	DeleteGraph(gameClearHandle);
	DeleteGraph(buttonBACKhandle);
	DeleteGraph(buttonAhandle);
	DeleteGraph(buttonBhandle);

	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);

	DeleteGraph(hanabiHandle1);
	DeleteGraph(hanabiHandle2);
	DeleteGraph(hanabiHandle3);
	DeleteGraph(hanabiHandle4);
	DeleteGraph(hanabiHandle5);
	DeleteGraph(hanabiHandle6);


	// 音楽のデリート
	DeleteSoundMem(musicClear);
	DeleteSoundMem(seButton);
	DeleteSoundMem(seBackButton);
	DeleteSoundMem(seHanabi);
}

void KeyGameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void KeyGameClearScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameClearHandle, true);


	// ランダムになっているか(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d\n", starnum);
	// フレーム数(デバック用)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "フレーム:% d\n", frameCount);
	
	// 花火を描画
	HanabiAnimation();

	// 星を描画
	StarAnimation();

	// 表示用文字

	ChangeFont("Lucida Bright");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	
	SetFontSize(150);
	DrawFormatString(250, 300, GetColor(255, 255, 133), "GAME CLEAR");


	DrawGraph(900, 550, buttonBACKhandle, true);
	DrawGraph(900, 660, buttonAhandle, true);
	DrawGraph(900, 760, buttonBhandle, true);


	ChangeFont("UD デジタル 教科書体 NK-B");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	SetFontSize(50);

	DrawFormatString(540, 600, GetColor(127, 255, 255), "TITLE");
	DrawFormatString(550, 700, GetColor(127, 255, 127), "NEXT");
	DrawFormatString(500, 800, GetColor(255, 127, 127), "RESTART");
	DrawFormatString(800, 600, GetColor(255, 255, 255), "・・・");
	DrawFormatString(800, 700, GetColor(255, 255, 255), "・・・");
	DrawFormatString(800, 800, GetColor(255, 255, 255), "・・・");


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}