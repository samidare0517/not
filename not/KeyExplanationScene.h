#pragma once
#include "Scene.h"
#include <memory>

class KeyExplanationScene : public Scene
{

public:

	KeyExplanationScene(SceneManager& manager);
	~KeyExplanationScene();

	void Update(const InputState& input);
	void Draw();

private:

	static constexpr int fadeIntarval = 60;
	int titleHandle = -1;		// タイトル画像
	int fadeTimer = fadeIntarval;		// フェードタイマー
	int fadeValue = 225;	// 黒矩形とのブレンド具合

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	// Update用メンバ関数ポインタ
	void (KeyExplanationScene::* updateFunc_)(const InputState& input);

	void Function();

};


