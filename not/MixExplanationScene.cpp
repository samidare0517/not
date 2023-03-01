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
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new MixField(manager_));
		return;
	}
}

void MixExplanationScene::Function()
{
}

MixExplanationScene::MixExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&MixExplanationScene::FadeInUpdate)
{
	// 画像のロード
	Handle = LoadGraph("data/MixGameSetumei.png");

	// SEの読み込み
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

MixExplanationScene::~MixExplanationScene()
{
	// 画像のデリート
	DeleteGraph(Handle);

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
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "三問目説明画面");
//	DrawFormatString(0, 500, GetColor(255, 255, 255),"(仮説明)\n");

	// 点滅処理
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		DrawFormatString(250, 800, GetColor(255, 255, 255), "ゲームをスタートするには");
		DrawFormatString(790, 800, GetColor(255, 0, 0), "RBボタン");
		DrawFormatString(995, 800, GetColor(255, 255, 255), "を押してください");
	}

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
