#pragma once
#include "Scene.h"

/// <summary>
/// キー問題用ゲームクリアシーン
/// </summary>
/// 
class KeyGameClearScene : public Scene
{
public:

	KeyGameClearScene(SceneManager& manager);
	~KeyGameClearScene();

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

	using UpdateFunc_t = void(KeyGameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};

