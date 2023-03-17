#include "MixTimeBar.h"
#include "MixField.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	bool timeflag = false;
	MixField* kMixField;
}

MixTimeBar::MixTimeBar()
{

}

MixTimeBar::~MixTimeBar()
{
	DeleteGraph(handle);
	DeleteGraph(mixTimeBackHandle);
}

void MixTimeBar::Init()
{
	tb = 1100;		// タイムバーの大きさ
	time = 4;		// 表示用のタイマー(4秒)
	timeflag = false;		// フラグの初期化
	handle = LoadGraph("data/tb.png");	// タイムバー用画像
	mixTimeBackHandle = LoadGraph("data/TimeBack.png");	// タイムバー用の背景画像
}

void MixTimeBar::Update()
{
	// 正解が押されたらタイムバーを画面サイズに戻す
	if (kMixField->AnswerFlag() == true)
	{
		tb = 1100;
		time = 4;
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

	int Mtime = 4;	// タイマーの数字
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

void MixTimeBar::Draw()
{
	// 数字をマイナスする(デバック用)
	SetFontSize(40);
	//	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	ChangeFont("UD デジタル 教科書体 NK-B");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント

	// ゲージ用のタイマー(表示用)
	DrawFormatString(510, 170, GetColor(255, 255, 255), "残り時間\n   %d秒", time);

	// タイムバーの背景
	DrawGraph(450, 25, mixTimeBackHandle, true);

	// タイムバー
	DrawExtendGraph(500, 100, tb, 0 + 50, handle, true);
}

bool MixTimeBar::Check()
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
