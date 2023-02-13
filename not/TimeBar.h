#pragma once
#include "Scene.h"
#include <memory>

class Field;
/// <summary>
/// タイムバー
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

	// フレーム
	int frame = 0;

	// 表示用のタイマー(3秒)
	int time = 3;

};
