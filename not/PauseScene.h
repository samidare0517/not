#pragma once
#include "Scene.h"

class InputState;
class SceneManager;

/// <summary>
/// ポーズシーン
/// </summary>

class PauseScene : public Scene
{
public:
	PauseScene(SceneManager& manager);
	virtual ~PauseScene();

	virtual void Update(const InputState& input) override;
	void CatInit();
	void CatAnimationDraw();
	void Draw();

private:
	
	int catHandle1 = -1;		// 猫アニメーション画像
	int catHandle2 = -1;
	int catHandle3 = -1;

	int catNum = 0;	// 猫の種類ランダム用
	int catRandomNum = 3;	// 全体の猫バリエーション

	int animationNumber = 0;                        //アニメーション（横）
	int imgidx = 2;                                 //縦の画像
	int timer = 0;                                  //アニメーションのインターバル

	int buttonSTARThandle = -1;	// 戻る案内用画像

	int seButtonPause = 0;	// ポーズシーンから移行するときのSEハンドル
};

