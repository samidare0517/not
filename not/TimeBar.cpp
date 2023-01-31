#include "TimeBar.h"
#include "DxLib.h"
#include "game.h"
#include "Field.h"

namespace
{
	bool timeflag = false;
	Field kfield;
}

TimeBar::TimeBar():
	tb(0),
	handle(0),
	frame(0)
{

}

TimeBar::~TimeBar()
{

}

void TimeBar::Init()
{
	tb = Game::kScreenWindth;		// タイムバーの大きさ
	handle = LoadGraph("Data/tb.png");	// タイムバー用画像
}

void TimeBar::Update()
{
	// フラグがtrueで帰ってきたらフラグを
	// 初期化する前にタイムバーを画面サイズに戻す
	if(timeflag == true)
	{
		tb = Game::kScreenWindth;
	}


	if (kfield.AnswerFlag() == true)
	{
		tb = Game::kScreenWindth;
	}


	timeflag = false;		// フラグの初期化

	frame++;
	// フレーム計算
	if (frame >= 60)
	{
		frame = 0;
		if (tb > 0)
		{
			tb -= 200;			// 1フレームで200ずつ減らす(1問あたり4秒)
		}
		if (tb <= 0)			// 0になったら0を入れる
		{
			tb = 0;
			timeflag = true;	// 0になったらtrueを返す
		}
	}
}

void TimeBar::Draw()
{
	// 数字をマイナスする(デバック用)
	SetFontSize(50);
	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	DrawExtendGraph(0, 0, tb, 0 + 50, handle, true);
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
