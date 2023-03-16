#include "MixExplanationScene.h"
#include "TimeBar.h"
#include "MixField.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void MixExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &MixExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void MixExplanationScene::NormalUpdate(const InputState& input)
{
	// 次へボタンが押されたら次のシーンへ移行する
	if (input.IsTriggred(InputType::next))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc_ = &MixExplanationScene::FadeOutUpdate;
	}
}

void MixExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<int>(fadeTimer) / static_cast<int>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new MixField(manager_));
		return;
	}
}

MixExplanationScene::MixExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&MixExplanationScene::FadeInUpdate)
{
	// 画像のロード
	Handle = LoadGraph("data/KeyGameSetumei.png");
	buttonAhandle = LoadGraph("data/button/buttonA.png");
	buttonBhandle = LoadGraph("data/button/buttonB.png");
	buttonXhandle = LoadGraph("data/button/buttonX.png");
	buttonYhandle = LoadGraph("data/button/buttonY.png");
	buttonPadhandle = LoadGraph("data/button/buttonPad.png");
	buttonLShandle = LoadGraph("data/button/buttonLS.png");

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

MixExplanationScene::~MixExplanationScene()
{
	// 画像のデリート
	DeleteGraph(Handle);
	DeleteGraph(buttonAhandle);
	DeleteGraph(buttonBhandle);
	DeleteGraph(buttonXhandle);
	DeleteGraph(buttonYhandle);
	DeleteGraph(buttonPadhandle);
	DeleteGraph(buttonLShandle);

	// 音楽のデリート
	DeleteSoundMem(seButton);
}

void MixExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void MixExplanationScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, Handle, true);
	DrawGraph(520, 558, buttonAhandle, true);
	DrawGraph(670, 558, buttonBhandle, true);
	DrawGraph(820, 558, buttonXhandle, true);
	DrawGraph(970, 558, buttonYhandle, true);
	DrawGraph(660, 460, buttonPadhandle, true);
	DrawGraph(830, 460, buttonLShandle, true);

	SetFontSize(50);
	DrawFormatString(550, 410, GetColor(127, 255, 127), "3問目はミックス問題です");

	DrawFormatString(770, 500, GetColor(255, 255, 255), "OR");
	DrawFormatString(520, 600, GetColor(255, 255, 255), "       &       &       &");


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
		DrawFormatString(680, 740, GetColor(255, 255, 77), "PUSH");
	}

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
