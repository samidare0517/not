#pragma once
#include "Scene.h"

class InputState;

// タイトルシーン
class TitleScene : public Scene
{
public:

	TitleScene(SceneManager& manager);
	virtual ~TitleScene();

	void Update(const InputState& input);

	void Draw();

private:

	int titleHandle = -1;		// タイトル画像
	int titlerogoHandle = -1;	// タイトルロゴ画像

	int starHandle1 = -1;		// 流れ星アニメーション画像
	int starHandle2 = -1;
	int starHandle3 = -1;
	
	int catHandle1 = -1;		// 猫アニメーション画像
	int catHandle2 = -1;
	int catHandle3 = -1;
	
	int buttonAhandle = -1;	// ボタン画像
	int buttonRBhandle = -1;	// RBボタン画像
	int buttonLBhandle = -1;	// LBボタン画像

	int indexX = 192;		//画像サイズのインデックス
	int indexY = 192;		//画像サイズのインデックス
	int posX = 0;			//今のアニメーション
	int posY = 0;
	int frameCount = 0;
	int frame = 0;
	
	int starNum = 0;// 星の種類ランダム用
	int starRandomNum = 3;// 全体の星バリエーション数
	int starX = 0;	// 星が描画されるX
	int starY = 0;	// 星が描画されるY

	int catNum = 0;	// 猫の種類ランダム用
	int catRandomNum = 3;	// 全体の猫バリエーション

	int animationNumber = 17;                        //アニメーション（横）
	int imgidx = 2;                                 //縦の画像
	int timer = 0;                                  //アニメーションのインターバル
	int catX = 1500;	// 猫の初期位置X
	int catY = 850;	// 猫の初期位置Y
	
	static constexpr int fadeIntarval = 60;
	int fadeTimer = fadeIntarval;		// フェードタイマー
	int fadeValue = 225;	// 黒矩形とのブレンド具合

	int musicTitle = 0;	// タイトルBGMハンドル
	int seButton = 0;	// 次に行くときのSEハンドル

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	// フェードアウト2時のUpdate関数
	void FadeOutUpdate2(const InputState& input);

	// フェードアウト3時のUpdate関数
	void FadeOutUpdate3(const InputState& input);

	// Update用メンバ関数ポインタ
	void (TitleScene::* updateFunc)(const InputState& input);

	// 星アニメーション時のDraw関数
	void StarAnimation();

	// 猫アニメーション時のDraw関数
	void CatAnimation();
};

