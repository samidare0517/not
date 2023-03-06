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

	timeflag = false;		// フラグの初期化


	frame++;
	// フレーム計算
	if (frame >= 60)
	{
		frame = 0;
		if (tb > 0)
		{
			tb -= 200;			// 1フレームで200ずつ減らす(1問あたり約3秒)
			time--;				// 表示する用の時間
		}
		if (tb <= 500)			// 500になったら500を入れる
		{
			tb = 500;
			timeflag = true;	// 500になったらtrueを返す
		}
	}
}

void TimeBar::Draw()
{
	// 数字をマイナスする(デバック用)
//	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

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
