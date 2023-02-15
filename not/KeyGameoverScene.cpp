#include "KeyGameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "KeyField.h"
#include "Pad.h"
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

KeyGameoverScene::KeyGameoverScene(SceneManager& manager) : Scene(manager),
updateFunc(&KeyGameoverScene::FadeInUpdate)
{
	// 画像のロード
	gameoverHandle = LoadGraph("data/OverBack.png");
}

KeyGameoverScene::~KeyGameoverScene()
{
	// 画像のデリート
	DeleteGraph(gameoverHandle);
}

void KeyGameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void KeyGameoverScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameoverHandle, true);

	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームオーバー");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

