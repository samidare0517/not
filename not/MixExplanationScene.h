#pragma once
#include "Scene.h"
#include <memory>

/// <summary>
/// ミックス問題用説明
/// </summary>
class MixExplanationScene : public Scene
{
public:

	MixExplanationScene(SceneManager& manager);
	~MixExplanationScene();

	void Update(const InputState& input);
	void Draw();

private:

	int seButton = 0;	// 次に行くときのSEハンドル

	static constexpr int fadeIntarval = 60;
	int Handle = -1;		// タイトル画像
	int fadeTimer = fadeIntarval;		// フェードタイマー
	int fadeValue = 225;	// 黒矩形とのブレンド具合

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	// Update用メンバ関数ポインタ
	void (MixExplanationScene::* updateFunc_)(const InputState& input);

	void Function();
};

