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
	~PauseScene();

	virtual void Update(const InputState& input) override;
	void Draw();

private:
	int Handle = -1;		// アニメーション画像
	int buttonSTARThandle = -1;	// 戻る案内用画像
	int animationNumber = 0;                        //アニメーション（横）
	int imgidx = 2;                                 //縦の画像
	int timer = 0;                                  //アニメーションのインターバル

	int seButtonPause = 0;	// ポーズシーンから移行するときのSEハンドル
};

