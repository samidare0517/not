#pragma once
#include "Scene.h"
#include <memory>

class ExplanationScene : public Scene
{
private:

	static constexpr int fade_intarval = 60;
	int titleH_ = -1;		// タイトル画像
	int fadeTimer_ = fade_intarval;		// フェードタイマー
	int fadeValue_ = 225;	// 黒矩形とのブレンド具合

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	// Update用メンバ関数ポインタ
	void (ExplanationScene::* updateFunc_)(const InputState& input);

	void Function();


public:

	ExplanationScene(SceneManager& manager);
	~ExplanationScene();

	void Update(const InputState& input);
	void Draw();

};


