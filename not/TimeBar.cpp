#include "TimeBar.h"
#include "DxLib.h"
#include "game.h"
#include "KeyField.h"
#include "PadField.h"

namespace
{
	bool timeflag = false;
	KeyField* kkey;
	PadField* kpad;
}

TimeBar::TimeBar()
{
	
}	

TimeBar::~TimeBar()
{
	DeleteGraph(handle);
	DeleteGraph(timeBackHandle);
}

void TimeBar::Init()
{
	tb = 1100;		// タイムバーの大きさ
	time = 3;		// 表示用のタイマー(3秒)
	timeflag = false;		// フラグの初期化
	handle = LoadGraph("data/tb.png");	// タイムバー用画像
	timeBackHandle = LoadGraph("data/TimeBack.png");	// タイムバー用の画像
}

void TimeBar::Update()
{
	// 正解が押されたらタイムバーを画面サイズに戻す
	if (kkey->AnswerFlag() == true)
	{
		tb = 1100;
		time = 3;
	}

	if (kpad->AnswerFlag() == true)
	{
		tb = 1100;
		time = 3;
	}

	frame++;
	// フレーム計算
	if (frame >= 60)
	{
		frame = 0;
		if (tb > 0)
		{
			time--;				// 表示する用の時間
		}
	}

	int Mtime = 3;	// タイマーの数字
	int Mtb = 1100;	// タイムバーの一番右
	float test = ((Mtb - static_cast<float>(500)) / Mtime) / 60;

	if (tb <= 500)
	{
		tb = 500;
	}
	else if (tb >= 500)
	{
		tb -= static_cast<int>(test);
	}
	if (time <= 0)
	{
		time = 0;
	}
	if (tb <= 500)
	{
		timeflag = true;
	}
//	printfDx("tb:%d\n", tb);
//	printfDx("frame:%d\n", frame);
}

void TimeBar::Draw()
{
	SetFontSize(40);
	// ゲージ用のタイマー(表示用)
	DrawFormatString(510, 170, GetColor(255, 255, 255), "残り時間\n   %d秒", time);
	
	// タイムバーの背景
	DrawGraph(450, 25, timeBackHandle, true);

	// タイムバー
	DrawExtendGraph(500, 100, tb, 0 + 50, handle, true);
}

bool TimeBar::Check()
{
	if (timeflag == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
