#pragma once
#include "Scene.h"

/// <summary>
/// パッド問題用ゲームオーバーシーン
/// </summary>

class PadGameoverScene : public Scene
{
public:

	PadGameoverScene(SceneManager& manager);
	virtual ~PadGameoverScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameoverHandle = -1;	// 画像
	int buttonBACKhandle = -1;	// BACKボタン画像
	int buttonBhandle = -1;		// Bボタン画像
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

	int musicOver = 0;	// ゲームオーバーBGMハンドル
	int seButton = 0;	// 次に行くときのSEハンドル
	int seBackButton = 0;	// タイトルへ戻るときのSEハンドル

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

	using UpdateFunc_t = void(PadGameoverScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;
};

