#pragma once
#include "Scene.h"

/// <summary>
/// ゲームクリアシーン
/// </summary>
class GameClearScene : public Scene
{
public:

	GameClearScene(SceneManager& manager);
	~GameClearScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameclearHandle = -1;	// 画像

	static constexpr int fadeInterval = 120;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(GameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc_ = nullptr;

};

