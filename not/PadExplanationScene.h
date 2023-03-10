#pragma once
#include "Scene.h"
#include <memory>

/// <summary>
/// パッド問題用説明
/// </summary>
 
class PadExplanationScene : public Scene
{
public:

	PadExplanationScene(SceneManager& manager);
	virtual ~PadExplanationScene();

	void Update(const InputState& input);
	void Draw();

private:

	int Handle = -1;		// タイトル画像
	int buttonAhandle = -1;	// Aボタン画像
	int buttonBhandle = -1;	// Bボタン画像
	int buttonXhandle = -1;	// Xボタン画像
	int buttonYhandle = -1;	// Yボタン画像

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
	void (PadExplanationScene::* updateFunc_)(const InputState& input);

	void Function();

};

