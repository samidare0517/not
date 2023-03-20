#pragma once
#include "Scene.h"

/// <summary>
/// ゲームセレクト画面
/// </summary>

class GameSelect : public Scene
{
public:

	GameSelect(SceneManager& manager);
	virtual ~GameSelect();

	void Update(const InputState& input);
	void Draw();

private:

	int backScreenHandle = -1;
	int buttonAhandle = -1;	// Aボタン画像
	int buttonBhandle = -1;	// Bボタン画像
	int buttonXhandle = -1;	// Xボタン画像
	int buttonRBHandle = -1;	// RBボタン画像

	int seButton = 0;	// 次に行くときのSEハンドル

	static constexpr int fadeInterval = 60;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate2(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate3(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate4(const InputState& input);


	// Update用メンバ関数ポインタ
	void (GameSelect::* updateFunc)(const InputState& input);

};

