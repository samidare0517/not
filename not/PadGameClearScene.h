#pragma once
#include "Scene.h"

/// <summary>
/// パッド問題用ゲームクリアシーン
/// </summary>

class PadGameClearScene : public Scene
{
public:

	PadGameClearScene(SceneManager& manager);
	~PadGameClearScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameclearHandle = -1;	// 画像
	int starHandle1 = -1;		// 流れ星アニメーション画像
	int starHandle2 = -1;
	int starHandle3 = -1;

	int indexX = 192;		//画像サイズのインデックス
	int indexY = 192;		//画像サイズのインデックス
	int posX = 0;			//今のアニメーション
	int posY = 0;
	int frameCount = 0;
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

	// アニメーション時のDraw関数
	void DrawAnimation();

	using UpdateFunc_t = void(PadGameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};

