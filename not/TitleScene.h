#pragma once
#include "Scene.h"

class InputState;

// タイトルシーン
class TitleScene : public Scene
{
public:

	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);
	void Draw();

private:

	int titleH_ = -1;		// タイトル画像

	static constexpr int fade_intarval = 60;
	int fadeTimer_ = fade_intarval;		// フェードタイマー
	int fadeValue_ = 225;	// 黒矩形とのブレンド具合

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	// Update用メンバ関数ポインタ
	void (TitleScene::* updateFunc_)(const InputState& input);

	void Function();

};

