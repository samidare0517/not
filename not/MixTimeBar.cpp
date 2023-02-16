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

}

void MixTimeBar::Init()
{
	mtb = 1100;		// タイムバーの大きさ
	time = 4;		// 表示用のタイマー(6秒)
	handle = LoadGraph("data/tb.png");	// タイムバー用画像
	mixTimeBackHandle = LoadGraph("data/TimeBack.png");	// タイムバー用の画像
	mixTimerBackHandle = LoadGraph("data/TimerBack.png");
}

void MixTimeBar::Update()
{
	// 正解が押されたらタイムバーを画面サイズに戻す
	if (kMixField->AnswerFlag() == true)
	{
		mtb = 1100;
		time = 4;
	}

	timeflag = false;		// フラグの初期化

	frame++;
	// フレーム計算
	if (frame >= 60)
	{
		frame = 0;
		if (mtb > 0)
		{
			mtb -= 150;			// 1フレームで200ずつ減らす(1問あたり約4秒)
			time--;				// 表示する用の時間
		}
		if (mtb <= 500)			// 500になったら500を入れる
		{
			mtb = 500;
			timeflag = true;	// 500になったらtrueを返す
		}
	}
}

void MixTimeBar::Draw()
{
	// 数字をマイナスする(デバック用)
	SetFontSize(50);
	//	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	DrawGraph(20, 20, mixTimerBackHandle, true);

	ChangeFont("UD デジタル 教科書体 NK-B");	//UD デジタル 教科書体 NK-Bに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント

	// ゲージ用のタイマー(表示用)
	DrawFormatString(75, 35, GetColor(255, 255, 255), "残り時間\n   %d秒", time);

	// タイムバーの背景
	DrawGraph(450, 25, mixTimeBackHandle, true);

	// タイムバー
	DrawExtendGraph(500, 100, mtb, 0 + 50, handle, true);
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
