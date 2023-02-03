#include "GameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "DxLib.h"

void GameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameoverScene::NormalUpdate;
		fadeValue_ = 0;
	}
}

void GameoverScene::NormalUpdate(const InputState& input)
{
	if (input.IsTriggred(InputType::next))
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
}

void GameoverScene::FadeOutUpdate(const InputState& input)
{

}

GameoverScene::GameoverScene(SceneManager& manager) : Scene(manager),
updateFunc_(&GameoverScene::FadeInUpdate)
{
	// 画像のロード
}

GameoverScene::~GameoverScene()
{
	// 画像のデリート(DeleteGraph(消したい画像ハンドル))
}

void GameoverScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameoverScene::Draw()
{
	DrawBox(200, 200, 400, 400, GetColor(255, 0, 255), true);
	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームオーバー");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
