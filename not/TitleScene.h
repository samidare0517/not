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

	int titleHandle = -1;		// タイトル画像

	static constexpr int fadeIntarval = 60;
	int fadeTimer = fadeIntarval;		// フェードタイマー
	int fadeValue = 225;	// 黒矩形とのブレンド具合

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	// Update用メンバ関数ポインタ
	void (TitleScene::* updateFunc)(const InputState& input);

	void Function();

};

