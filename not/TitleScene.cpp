#include "KeyExplanationScene.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "KeyGameoverScene.h"
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
		updateFunc = &TitleScene::FadeOutUpdate;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyExplanationScene(manager_));
		return;
	}
}


TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
updateFunc(&TitleScene::FadeInUpdate)
{
	// 画像のロード
	titleHandle = LoadGraph("data/TitleBack.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");
}

TitleScene::~TitleScene()
{
	// 画像のデリート
	DeleteGraph(titleHandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);
}

void TitleScene::Update(const InputState& input)
{
	(this ->*updateFunc)(input);
}


void TitleScene::Draw()
{
	// 背景描画
	DrawGraph(0, 0, titleHandle, true);
	
	//	printfDx("%d\n", left);	// デバック用
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	starnum = rand() % randomnum + 1;		// 1～3の乱数を出す
	starX = rand() % 1400 + 192;	// 192～1400のランダムな数値 (画面内に描画)
	starY = rand() % 650  + 192;	// 192～700のランダムな数値 (画面内に描画)

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
	DrawFormatString(0, 200, GetColor(255, 255, 255), "星:% d", starnum);
	printfDx("%d\n", frameCount);
	
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

	
	ChangeFont("UD デジタル 教科書体 NK-B");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	
	SetFontSize(100);
	DrawFormatString(600, 400, GetColor(255, 255, 255), "タイトル");
	
	// 点滅処理
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}

	if (BrinkCounter < 80)
	{
		SetFontSize(50);
		DrawFormatString(500, 600, GetColor(255, 255, 0), "RBボタンを押してください");
	}

	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトル");

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	
	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
