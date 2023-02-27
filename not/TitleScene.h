#pragma once
#include "Scene.h"

class InputState;

// タイトルシーン
class TitleScene : public Scene
{
public:

	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);

	void Draw();

private:

	int titleHandle = -1;		// タイトル画像
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
	void (TitleScene::* updateFunc)(const InputState& input);
;

};

