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
	int starHandle1 = -1;		// 流れ星アニメーション画像
	int starHandle2 = -1;
	int starHandle3 = -1;

	int left = 0;
	int top = 0;
	int rigth = 192;
	int bottom = 192;
	int frameCount = 0;
	float changeY = false;
	int frame = 0;

	int starnum = 0;// 星の種類ランダム用
	int randomnum = 3;// 全体の問題バリエーション数
	int starX = 0;	// 星が描画されるX
	int starY = 0;	// 星が描画されるY

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

