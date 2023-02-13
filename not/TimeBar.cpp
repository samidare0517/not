#include "TimeBar.h"
#include "DxLib.h"
#include "game.h"
#include "Field.h"

namespace
{
	bool timeflag = false;
	Field* kfield;
}

TimeBar::TimeBar()
{
	
}	

TimeBar::~TimeBar()
{
	
}

void TimeBar::Init()
{
	tb = 1100;		// タイムバーの大きさ
	handle = LoadGraph("data/tb.png");	// タイムバー用画像
}

void TimeBar::Update()
{
	// 正解が押されたらタイムバーを画面サイズに戻す
	if (kfield->AnswerFlag() == true)
	{
		tb = 1100;
	}

	timeflag = false;		// フラグの初期化

	frame++;
	// フレーム計算
	if (frame >= 60)
	{
		frame = 0;
		if (tb > 0)
		{
			tb -= 200;			// 1フレームで200ずつ減らす(1問あたり3秒)
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
	SetFontSize(50);
	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	DrawExtendGraph(500, 120, tb, 0 + 50, handle, true);
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
