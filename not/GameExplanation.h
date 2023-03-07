#pragma once
#include "Scene.h"

class InputState;

/// <summary>
/// ゲーム全体説明
/// </summary>

class GameExplanation : public Scene
{
public:

	GameExplanation(SceneManager& manager);
	~GameExplanation();

	void Update(const InputState& input);

	void Draw();

private:

	int explanationHandle = -1;		// タイトル画像
	int buttonRBhandle = -1;	// RBボタン画像
	int musicTitle = 0;	// タイトルBGMハンドル
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
	void (GameExplanation::* updateFunc)(const InputState& input);


};

