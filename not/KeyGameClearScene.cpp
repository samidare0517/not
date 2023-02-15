#include "KeyGameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "KeyField.h"
#include "DxLib.h"

void KeyGameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &KeyGameClearScene::NormalUpdate;
		fadeValue = 0;
	}
}

void KeyGameClearScene::NormalUpdate(const InputState& input)
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

void KeyGameClearScene::FadeOutUpdate(const InputState& input)
{

}

KeyGameClearScene::KeyGameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&KeyGameClearScene::FadeInUpdate)
{
	// 画像のロード
	gameclearHandle = LoadGraph("data/ClearBack.png");
}

KeyGameClearScene::~KeyGameClearScene()
{
	// 画像のデリート
	DeleteGraph(gameclearHandle);
}

void KeyGameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void KeyGameClearScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameclearHandle, true);

	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームクリア");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}