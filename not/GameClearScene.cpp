#include "GameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Field.h"
#include "DxLib.h"

void GameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameClearScene::NormalUpdate;
		fadeValue_ = 0;
	}
}

void GameClearScene::NormalUpdate(const InputState& input)
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

void GameClearScene::FadeOutUpdate(const InputState& input)
{

}

GameClearScene::GameClearScene(SceneManager& manager) : Scene(manager),
updateFunc_(&GameClearScene::FadeInUpdate)
{
	// 画像のロード
	gameclearH = LoadGraph("data/ClearBack.png");
}

GameClearScene::~GameClearScene()
{
	// 画像のデリート
	DeleteGraph(gameclearH);
}

void GameClearScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameClearScene::Draw()
{
	// 普通の描画
	DrawGraph(0, 0, gameclearH, true);

	/*SetFontSize(100);
	DrawFormatString(500, 400, GetColor(255, 255, 255), "ゲームクリア");*/

	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームクリア");

	/*SetFontSize(50);
	DrawFormatString(500, 700, GetColor(255, 255, 255),
		"リスタート→スペースキー\nタイトル　→エンターキー");*/

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}