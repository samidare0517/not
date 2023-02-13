#include "PauseScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


PauseScene::PauseScene(SceneManager& manager) : Scene(manager)
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(const InputState& input)
{
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PopScene();
		return;
	}
}

void PauseScene::Draw()
{
	constexpr int pw_width = 500;	// ポーズ枠の幅
	constexpr int pw_height = 500;	// ポーズ枠の高さ
	constexpr int pw_start_x = (1600 - pw_width) / 2;	// ポーズ枠左
	constexpr int pw_start_y = (900 - pw_height) / 2;	// ポーズ枠上

//	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);	// 乗算合成

	// ポーズウィンドウセロファン(黒)
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width,
		pw_start_y + pw_height,
		GetColor(188, 221, 255), true);

	// 通常描画に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width,
		pw_start_y + pw_height,
		0xffffff, false);

	// ポーズ中メッセージ
	SetFontSize(50);
	DrawString(pw_start_x + 10, pw_start_y + 10, "Pauseing", GetColor(255, 255, 127));
}
