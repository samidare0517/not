#include "TimeBar.h"
#include "KeyField.h"
#include "KeyExplanationScene.h"
#include "GameExplanation.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void KeyExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &KeyExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void KeyExplanationScene::NormalUpdate(const InputState& input)
{
	// ボタンが押されたらゲームシーンへ移行する
	if (input.IsTriggred(InputType::next))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc_ = &KeyExplanationScene::FadeOutUpdate;
	}

	// RBボタンが押されたらゲーム説明のシーンへ移行する
	if (input.IsTriggred(InputType::button))
	{
		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SEを呼び出す
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);
		updateFunc_ = &KeyExplanationScene::FadeOutUpdate2;
	}
}

void KeyExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void KeyExplanationScene::FadeOutUpdate2(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new GameExplanation(manager_));
		return;
	}
}

KeyExplanationScene::KeyExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&KeyExplanationScene::FadeInUpdate)
{
	// 画像のロード
	Handle = LoadGraph("data/KeyGameSetumei.png");
	buttonAhandle = LoadGraph("data/button/buttonA.png");
	buttonRBhandle = LoadGraph("data/button/buttonRB.png");
	buttonPadhandle = LoadGraph("data/button/buttonPad.png");
	buttonLShandle = LoadGraph("data/button/buttonLS.png");

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

KeyExplanationScene::~KeyExplanationScene()
{
	// 画像のデリート
	DeleteGraph(Handle);
	DeleteGraph(buttonAhandle);
	DeleteGraph(buttonRBhandle);
	DeleteGraph(buttonPadhandle);
	DeleteGraph(buttonLShandle);

	// 音楽のデリート
	DeleteSoundMem(seButton);
}

void KeyExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void KeyExplanationScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0,Handle, true);
	DrawGraph(860, 600, buttonRBhandle, true);
	DrawGraph(645, 435, buttonPadhandle, true);
	DrawGraph(810, 440, buttonLShandle, true);


	SetFontSize(40);
	DrawFormatString(660, 620, GetColor(255, 255, 77), "ゲーム説明");
	SetFontSize(50);
	DrawFormatString(550, 390, GetColor(127, 255, 127), "1問目は方向問題です");
	DrawFormatString(750, 480, GetColor(255, 255, 255), "OR");
	
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
