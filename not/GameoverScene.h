#pragma once
#include "Scene.h"

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class GameoverScene : public Scene
{
private:
	int gameoverH = -1;	// 画像

	static constexpr int fade_interval = 120;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;
	using UpdateFunc_t = void(GameoverScene::*)(const InputState&);
	UpdateFunc_t updateFunc_ = nullptr;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

public:
	GameoverScene(SceneManager& manager);
	~GameoverScene();

	void Update(const InputState& input);
	void Draw();
};

