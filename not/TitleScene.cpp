#include "TimeBar.h"
#include "Field.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "GameoverScene.h"
#include "DxLib.h"

void TitleScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = fadeTimer_;
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &TitleScene::NormalUpdate;
		fadeValue_ = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	// 次へボタンが押されたら次のシーンへ移行する
	if (input.IsTriggred(InputType::next))
	{
		updateFunc_ = &TitleScene::FadeOutUpdate;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_intarval));
	if (++fadeTimer_ == fade_intarval)
	{
		manager_.CangeScene(new Field(manager_));
		return;
	}
}

void TitleScene::Function()
{
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
updateFunc_(&TitleScene::FadeInUpdate)
{
	// 画像のロード
}

TitleScene::~TitleScene()
{
	// 画像のデリート
}

void TitleScene::Update(const InputState& input)
{
	(this ->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	// 普通の描画
	//DrawRotaGraph(320, 240, 1.0f, 0.0f, titleH_, true);
	
	SetFontSize(100);
	DrawFormatString(250, 400, GetColor(255, 255, 255), "タイトル");
	
	// シーン確認用
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトル");

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	
	// 画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, 900, 900, GetColor(255, 0, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
