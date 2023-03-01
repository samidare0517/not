#include "PadGameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PadField.h"
#include "MixExplanationScene.h"
#include <time.h>		// ランダム用
#include "DxLib.h"

void PadGameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &PadGameClearScene::NormalUpdate;
		fadeValue = 0;
	}
}

void PadGameClearScene::NormalUpdate(const InputState& input)
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

		manager_.CangeScene(new MixExplanationScene(manager_));
		return;
	}
	// リスタートの場合
	if (input.IsTriggred(InputType::prev))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		manager_.CangeScene(new PadField(manager_));
		return;
	}
}

void PadGameClearScene::FadeOutUpdate(const InputState& input)
{

}

void PadGameClearScene::DrawAnimation()
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

	if (frameCount > 2)	//2フレームごとに画像を右に192移動させる
	{
		frameCount = 0;	// フレームカウントをリセット
		posX++;	//1をプラスする
	}
	if (posX >= 5)	// 画像の右まで移動すると左に戻す
	{
		posX = 0;	//0に戻す
		posY += 1;	// アニメーションを一段下げる

	}
	if (posY >= 4)	//一番最後の段より大きくなろうとしたら
	{
		posY = 0;	//ゼロに戻す

		//一番最後まで行ったら場所をランダムで生成する
		srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
		starnum = rand() % randomnum + 1;		// 1～3の乱数を出す
		starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
		starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)
	}
}

PadGameClearScene::PadGameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&PadGameClearScene::FadeInUpdate)
{
	// 画像のロード
	gameclearHandle = LoadGraph("data/ClearBack.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");

	//初期化
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	starnum = rand() % randomnum + 1;		// 1～3の乱数を出す
	starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
	starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)

	// BGMの読みこみ
	musicClear = LoadSoundMem("data/BGM/GameClearBGM.mp3");

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");

	// SEの読み込み
	seBackButton = LoadSoundMem("data/BGM/BackTitleSE.mp3");
}

PadGameClearScene::~PadGameClearScene()
{
	// 画像のデリート
	DeleteGraph(gameclearHandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);

	// 音楽のデリート
	DeleteSoundMem(musicClear);
	DeleteSoundMem(seButton);
	DeleteSoundMem(seBackButton);
}

void PadGameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void PadGameClearScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameclearHandle, true);

	// BGMの音量を調整する
	ChangeVolumeSoundMem(255 * 50 / 100, musicClear);

	// BGMを呼び出す
	PlaySoundMem(musicClear, DX_PLAYTYPE_LOOP, false);

	// ランダムになっているか(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d\n", starnum);
	// フレーム数(デバック用)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "フレーム:% d\n", frameCount);

	DrawAnimation();	// アニメーションを呼び出す

	// 表示用文字

	ChangeFont("Lucida Bright");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	SetFontSize(150);
	DrawFormatString(250, 300, GetColor(255, 255, 133), "GAME CLEAR");

	ChangeFont("UD デジタル 教科書体 NK-B");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	SetFontSize(50);
	DrawFormatString(500, 600, GetColor(255, 255, 255),
		" タイトル  ・・・ BACK\n\n次の問題 ・・・ RB\n\nリスタート ・・・ LB");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}