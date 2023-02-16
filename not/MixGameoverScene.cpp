#include "MixGameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MixField.h"
#include "Pad.h"
#include "DxLib.h"

void MixGameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &MixGameoverScene::NormalUpdate;
		fadeValue = 0;
	}
}

void MixGameoverScene::NormalUpdate(const InputState& input)
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
		manager_.CangeScene(new MixField(manager_));
		return;
	}
}

void MixGameoverScene::FadeOutUpdate(const InputState& input)
{

}

MixGameoverScene::MixGameoverScene(SceneManager& manager) : Scene(manager),
updateFunc(&MixGameoverScene::FadeInUpdate)
{
	// 画像のロード
//	gameoverHandle = LoadGraph("data/OverBack.png");
}

MixGameoverScene::~MixGameoverScene()
{
	// 画像のデリート
//	DeleteGraph(gameoverHandle);
}

void MixGameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void MixGameoverScene::Draw()
{
	// 普通の描画
//	DrawGraph(0, 0, gameoverHandle, true);

	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Mixゲームオーバー");
	DrawFormatString(500, 500, GetColor(255, 255, 255), "タイトル→T\nリスタート→スペース");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

