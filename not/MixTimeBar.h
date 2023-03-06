#pragma once

/// <summary>
/// ミックス用タイムバー
/// </summary>

class MixTimeBar
{
public:

	MixTimeBar();
	~MixTimeBar();

	void Init();
	void Update();
	void Draw();

	bool Check();

private:

	// タイムバー
	int mtb = 0;

	// 画像ハンドル
	int handle = 0;

	// タイムバー用の背景ハンドル
	int mixTimeBackHandle = 0;

	// フレーム
	int frame = 0;

	// 表示用タイマー
	int time = 4;

};

