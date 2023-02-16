#include "TimeBar.h"
#include "KeyField.h"
#include "ExplanationScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void ExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &ExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void ExplanationScene::NormalUpdate(const InputState& input)
{
	// 次へボタンが押されたら次のシーンへ移行する
	if (input.IsTriggred(InputType::next))
	{
		updateFunc_ = &ExplanationScene::FadeOutUpdate;
	}
}

void ExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void ExplanationScene::Function()
{
}

ExplanationScene::ExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&ExplanationScene::FadeInUpdate)
{
	// 画像のロード
}

ExplanationScene::~ExplanationScene()
{
	// 画像のデリート
}

void ExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void ExplanationScene::Draw()
{
	// 普通の描画
	//DrawRotaGraph(320, 240, 1.0f, 0.0f, titleH_, true);
	DrawBox(200, 200, 400, 400, GetColor(255, 255, 255), true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "説明画面");
	DrawFormatString(0, 500, GetColor(255, 255, 255), 
		"(仮説明)\n"
		"真ん中に表示される指示の通りに\nパッドの十字キーやボタンを押してください。\n"
		"・一問目は方向\n・二問目はボタン\n・三問目は方向とボタンのミックスです。\n"
		"ゲームをスタートするにはRBボタンを押してください。");

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// 画面全体を青に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(30, 144, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
