#pragma once
#include "Scene.h"
#include <memory>

/// <summary>
/// キーの問題説明
/// </summary>

class KeyExplanationScene : public Scene
{

public:

	KeyExplanationScene(SceneManager& manager);
	virtual ~KeyExplanationScene();

	void Update(const InputState& input);
	void Draw();

private:

	int Handle = -1;		// 画像
	int buttonAhandle = -1;	// Aボタン画像
	int buttonPadhandle = -1;	// 十字ボタン画像

	int seButton = 0;	// 次に行くときのSEハンドル

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
	void (KeyExplanationScene::* updateFunc_)(const InputState& input);


};


