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
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
	// 次の問題に進む場合
	if (input.IsTriggred(InputType::next))
	{
		manager_.CangeScene(new MixExplanationScene(manager_));
		return;
	}
	// リスタートの場合
	if (input.IsTriggred(InputType::prev))
	{
		manager_.CangeScene(new PadField(manager_));
		return;
	}
}

void PadGameClearScene::FadeOutUpdate(const InputState& input)
{

}

PadGameClearScene::PadGameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&PadGameClearScene::FadeInUpdate)
{
	// 画像のロード
	gameclearHandle = LoadGraph("data/ClearBack.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");
}

PadGameClearScene::~PadGameClearScene()
{
	// 画像のデリート
	DeleteGraph(gameclearHandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);
}

void PadGameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void PadGameClearScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameclearHandle, true);

	//	printfDx("%d\n", left);	// デバック用
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	starnum = rand() % randomnum + 1;		// 1～3の乱数を出す
	starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
	starY = rand() % 650 + 192;	// 192～700のランダムな数値 (画面内に描画)


	frameCount++;

	if (frameCount == 3)	//3フレームごとに画像を右に192移動させる
	{
		frameCount = 0;	// フレームカウントをリセット
		left += 192;	// 192をプラスする
	}
	if (left == 960)	// 画像の右まで移動すると左に戻す
	{
		left = 0;
		changeY = true;	// 画像を下に192移動
	}
	if (changeY)	// 画像を下に192移動
	{
		top += 192;
		changeY = false;
	}
	if (top == 768)
	{
		top = 0;
	}


	// ランダムになっているか(デバック用)
	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d\n", starnum);
	// フレーム数(デバック用)
	DrawFormatString(0, 300, GetColor(255, 255, 255), "フレーム:% d\n", frameCount);

	// ランダムにアニメーションを描画
	switch (starnum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
			left, top, rigth, bottom,
			1, 0, starHandle1, true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
			left, top, rigth, bottom,
			1, 0, starHandle2, true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
			left, top, rigth, bottom,
			1, 0, starHandle3, true, false);
		break;
	}

	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "padゲームクリア");
	DrawFormatString(500, 500, GetColor(255, 255, 255),
		"タイトル→BACK\n次の問題→RB\nリスタート→LB");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}