#pragma once
#include "Scene.h"

/// <summary>
/// パッド問題用ゲームクリアシーン
/// </summary>

class MixGameClearScene : public Scene
{
public:

	MixGameClearScene(SceneManager& manager);
	virtual ~MixGameClearScene();

	void Update(const InputState& input);
	void HanabiAnimation();
	void Draw();

private:

	int gameclearHandle = -1;	// 画像
	int buttonBACKhandle = -1;	// BACKボタン画像
	int buttonBhandle = -1;		// Bボタン画像
	
	int starHandle1 = -1;		// 流れ星アニメーション画像
	int starHandle2 = -1;
	int starHandle3 = -1;

	int hanabiHandle1 = -1;		// 花火アニメーション
	int hanabiHandle2 = -1;
	int hanabiHandle3 = -1;
	int hanabiHandle4 = -1;
	int hanabiHandle5 = -1;
	int hanabiHandle6 = -1;

	int starIndexX = 192;		//画像サイズのインデックス
	int starIndexY = 192;		//画像サイズのインデックス
	int starPosX = 0;			//今のアニメーション
	int starPosY = 0;
	int frameCount = 0;
	int frame = 0;

	int starNum = 0;// 星の種類ランダム用
	int randomNum = 3;// 全体の問題バリエーション数
	int starX = 0;	// 星が描画されるX
	int starY = 0;	// 星が描画されるY

	int hanabiAnimationNumber = 0;
	int hanabiImgIdx = 0;
	int timer = 0;

	int hanabiNum = 0;	// 花火の種類ランダム用
	int hanabiRandomNum = 3;	// 花火のパターンの数

	int musicClear = 0;	// クリアBGMハンドル
	int seButton = 0;	// 次に行くときのSEハンドル
	int seBackButton = 0;	// タイトルへ戻るときのSEハンドル

	static constexpr int fadeInterval = 60;
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

	using UpdateFunc_t = void(MixGameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};

