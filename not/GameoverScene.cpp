#include "GameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Field.h"
#include "Pad.h"
#include "DxLib.h"

void GameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &GameoverScene::NormalUpdate;
		fadeValue = 0;
	}
}

void GameoverScene::NormalUpdate(const InputState& input)
{
	// タイトルの場合
	if (input.IsTriggred(InputType::next))
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
	// リスタートの場合
	if (input.IsTriggred(InputType::prev))
	{
		manager_.CangeScene(new Field(manager_));
		return;
	}
}

void GameoverScene::FadeOutUpdate(const InputState& input)
{

}

GameoverScene::GameoverScene(SceneManager& manager) : Scene(manager),
updateFunc(&GameoverScene::FadeInUpdate)
{
	// 画像のロード
	gameoverHandle = LoadGraph("data/OverBack.png");
}

GameoverScene::~GameoverScene()
{
	// 画像のデリート
	DeleteGraph(gameoverHandle);
}

void GameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void GameoverScene::Draw()
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

