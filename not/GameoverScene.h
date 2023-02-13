#pragma once
#include "Scene.h"

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class GameoverScene : public Scene
{
public:

	GameoverScene(SceneManager& manager);
	~GameoverScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameoverH = -1;	// 画像

	static constexpr int fade_interval = 120;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(GameoverScene::*)(const InputState&);
	UpdateFunc_t updateFunc_ = nullptr;

};

