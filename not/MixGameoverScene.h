#pragma once
#include "Scene.h"

/// <summary>
/// ミックス問題用ゲームオーバーシーン
/// </summary>

class MixGameoverScene : public Scene
{
public:

	MixGameoverScene(SceneManager& manager);
	~MixGameoverScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameoverHandle = -1;	// 画像

	static constexpr int fadeInterval = 120;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(MixGameoverScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;
};

