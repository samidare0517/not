#pragma once
#include "Scene.h"
#include <memory>

class KeyField;
class PadField;

/// <summary>
/// 通常用タイムバー
/// </summary>

class TimeBar
{
public:

	TimeBar();
	~TimeBar();

	void Init();
	void Update();
	void Draw();

	bool Check();
	
private:

	// タイムバー
	int tb = 0;

	// 画像ハンドル
	int handle = 0;

	// タイムバー用の背景ハンドル
	int timeBackHandle = 0;

	// フレーム
	int frame = 0;

	// 表示用タイマー
	int time = 3;

};
