#include "MixGameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MixField.h"
#include "Pad.h"
#include <time.h>		// ランダム用
#include "DxLib.h"

void MixGameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &MixGameoverScene::NormalUpdate;
		fadeValue = 0;
	}
}

void MixGameoverScene::NormalUpdate(const InputState& input)
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
	// リスタートの場合
	if (input.IsTriggred(InputType::prev))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		manager_.CangeScene(new MixField(manager_));
		return;
	}
}

void MixGameoverScene::FadeOutUpdate(const InputState& input)
{

}

void MixGameoverScene::DrawAnimation()
{
	// ランダムにアニメーションを描画
	switch (starnum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
			indexX * posX, indexY * posY, indexX, indexY,
			1, 0, starHandle1, true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
			indexX * posX, indexY * posY, indexX, indexY,
			1, 0, starHandle2, true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
			indexX * posX, indexY * posY, indexX, indexY,
			1, 0, starHandle3, true, false);
		break;
	}

	frameCount++;

	if (frameCount > 2)	// 2フレームごとに画像を右に192移動させる
	{
		frameCount = 0;	// フレームカウントをリセット
		posX++;	// 1をプラスする
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
		starnum = rand() % randomnum + 1;		// 1～3の乱数を出す
		starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
		starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)
	}
}

MixGameoverScene::MixGameoverScene(SceneManager& manager) : Scene(manager),
updateFunc(&MixGameoverScene::FadeInUpdate)
{
	// 画像のロード
	gameoverHandle = LoadGraph("data/OverBack.png");
	buttonBACKhandle = LoadGraph("data/button/buttonBACK.png");
	buttonBhandle = LoadGraph("data/button/buttonB.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");

	//初期化
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	starnum = rand() % randomnum + 1;		// 1～3の乱数を出す
	starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
	starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)

	// BGMの読みこみ
	musicOver = LoadSoundMem("data/BGM/GameOverBGM.mp3");

	// BGMの音量を調整する
	ChangeVolumeSoundMem(255 * 50 / 100, musicOver);

	// BGMを呼び出す
	PlaySoundMem(musicOver, DX_PLAYTYPE_LOOP, false);

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");

	// SEの読み込み
	seBackButton = LoadSoundMem("data/BGM/BackTitleSE.mp3");

}

MixGameoverScene::~MixGameoverScene()
{
	// 画像のデリート
	DeleteGraph(gameoverHandle);
	DeleteGraph(buttonBACKhandle);
	DeleteGraph(buttonBhandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);

	// 音楽のデリート
	DeleteSoundMem(musicOver);
	DeleteSoundMem(seButton);
	DeleteSoundMem(seBackButton);
}

void MixGameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void MixGameoverScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameoverHandle, true);
	
	// ランダムになっているか(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d\n", starnum);
	// フレーム数(デバック用)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "フレーム:% d\n", frameCount);

	DrawAnimation();	// アニメーションを呼び出す

	// 表示用文字
	ChangeFont("Comic Sans MS");	// Comic Sans MSに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	SetFontSize(150);
	DrawFormatString(260, 300, GetColor(191, 127, 255), "GAME OVER...");


	DrawGraph(900, 550, buttonBACKhandle, true);
	DrawGraph(900, 660, buttonBhandle, true);


	ChangeFont("UD デジタル 教科書体 NK-B");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	SetFontSize(50);

	DrawFormatString(540, 600, GetColor(127, 255, 255), "TITLE");
	DrawFormatString(500, 700, GetColor(255, 127, 127), "RESTART");
	DrawFormatString(800, 600, GetColor(255, 255, 255), "・・・");
	DrawFormatString(800, 700, GetColor(255, 255, 255), "・・・");


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

