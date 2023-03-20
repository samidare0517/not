#include "PadExplanationScene.h"
#include "TimeBar.h"
#include "PadField.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void PadExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &PadExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void PadExplanationScene::NormalUpdate(const InputState& input)
{
	// 次へボタンが押されたら次のシーンへ移行する
	if (input.IsTriggred(InputType::next))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc_ = &PadExplanationScene::FadeOutUpdate;
	}
}

void PadExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new PadField(manager_));
		return;
	}
}

PadExplanationScene::PadExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&PadExplanationScene::FadeInUpdate)
{
	// 画像のロード
	Handle = LoadGraph("data/KeyGameSetumei.png");
	buttonAhandle = LoadGraph("data/button/buttonA.png");
	buttonBhandle = LoadGraph("data/button/buttonB.png");
	buttonXhandle = LoadGraph("data/button/buttonX.png");
	buttonYhandle = LoadGraph("data/button/buttonY.png");
	
	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

PadExplanationScene::~PadExplanationScene()
{
	// 画像のデリート
	DeleteGraph(Handle);
	DeleteGraph(buttonAhandle);
	DeleteGraph(buttonBhandle);
	DeleteGraph(buttonXhandle);
	DeleteGraph(buttonYhandle);

	// 音楽のデリート
	DeleteSoundMem(seButton);
}

void PadExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void PadExplanationScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, Handle, true);
	DrawGraph(510, 458, buttonAhandle, true);
	DrawGraph(660, 458, buttonBhandle, true);
	DrawGraph(810, 458, buttonXhandle, true);
	DrawGraph(960, 458, buttonYhandle, true);

	SetFontSize(50);
	DrawFormatString(550, 410, GetColor(127, 255, 127),
		"2問目はボタン問題です");
	DrawFormatString(510, 500, GetColor(255, 255, 255),
		"       &       &       &");

	// 点滅処理
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		DrawGraph(810, 700, buttonAhandle, true);
		DrawFormatString(680, 740, GetColor(255, 255, 77), "NEXT");
	}

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
