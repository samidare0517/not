#include "KeyGameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "KeyField.h"
#include "Pad.h"
#include <time.h>		// ランダム用
#include "DxLib.h"

void KeyGameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &KeyGameoverScene::NormalUpdate;
		fadeValue = 0;
	}
}

void KeyGameoverScene::NormalUpdate(const InputState& input)
{
	// タイトルの場合
	if (input.IsTriggred(InputType::title))
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
	// リスタートの場合
	if (input.IsTriggred(InputType::prev))
	{
		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void KeyGameoverScene::FadeOutUpdate(const InputState& input)
{

}

void KeyGameoverScene::DrawAnimation()
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

KeyGameoverScene::KeyGameoverScene(SceneManager& manager) : Scene(manager),
updateFunc(&KeyGameoverScene::FadeInUpdate)
{
	// 画像のロード
	gameoverHandle = LoadGraph("data/OverBack.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");

	//初期化
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	starnum = rand() % randomnum + 1;		// 1～3の乱数を出す
	starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
	starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)
}

KeyGameoverScene::~KeyGameoverScene()
{
	// 画像のデリート
	DeleteGraph(gameoverHandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);
}

void KeyGameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void KeyGameoverScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameoverHandle, true);

	// ランダムになっているか(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d\n", starnum);
	// フレーム数(デバック用)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "フレーム:% d\n", frameCount);

	DrawAnimation();

	// 表示用文字
	ChangeFont("Lucida Bright");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	SetFontSize(150);
	DrawFormatString(260, 300, GetColor(191, 127, 255), "GAME OVER");

	ChangeFont("UD デジタル 教科書体 NK-B");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	SetFontSize(50);
	DrawFormatString(500, 600, GetColor(255, 255, 255),
		"  タイトル    ・・・ BACK\n\nリスタート   ・・・ LB");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

