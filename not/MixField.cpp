#include "MixField.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "MixGameoverScene.h"
#include "MixGameClearScene.h"
#include "PauseScene.h"
#include "DxLib.h"
#include "Pad.h"
#include <time.h>		// ランダム用
#include "MixTimeBar.h"

namespace
{
	// ランダム用
	int num = 0;

	// 全体の問題バリエーション数
	int randomnum = 16;

	// 問題の文字表示位置
	int mozi0X = 765;	// 通常用
	int mozi0Y = 400;	// 通常用

	int mozi1X = 765;	// じゃない用一行目
	int mozi1Y = 350;	// じゃない用一行目

	int mozi2X = 640;	// じゃない用二行目
	int mozi2Y = 450;	// じゃない用二行目

	bool answerCheck = false;

	// 問題を繰り返す回数
	int questionNum = 30;

	// 表示用問題数
	int question = 30;

	// 問題の正解回数
	int answerNum = 0;

	// 背景用ハンドル
	int handle = 0;

	MixTimeBar kMixTime;
}

void MixField::FadeInUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &MixField::NormalUpdate;
	}
}

MixField::MixField(SceneManager& manager) :Scene(manager),
updateFunc(&MixField::FadeInUpdate)
{
	Init();
}

MixField::~MixField()
{
}

void MixField::Init()
{
	handle = LoadGraph("data/Back.png");	// タイムバー用画像

	kMixTime.Init();

	answerNum = 0;	// 問題の正解数カウントを0にする(初期化)

	question = 30;	// 残り問題数を初期化

	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	num = rand() % randomnum + 1;		// 1～8の乱数を出す
}

void MixField::NormalUpdate(const InputState& input)
{

	// 背景描画 (デバック文字が見えるように背景を表示)
//	DrawGraph(0, 0, handle, true);

	Pad::Update();
	kMixTime.Update();

	if (answerCheck == true)	// 正解が押されたら次の問題へ
	{
		for (int i = 0; i < questionNum; i++)		// 30問繰り返す
		{
			num = rand() % randomnum + 1;
		}
		answerNum++;
		question--;
	}
	else if (kMixTime.Check() == true)	// タイムバーが0になっていたらゲームオーバー処理へ
	{
		TimeUp();
	}

	// 正解数が30になったらクリア画面へ
	SetFontSize(50);
	if (answerNum == 30)
	{
		answerCheck = false;	// 正解のフラグの初期化

		// 指定の回数正解したらゲームクリアシーンに行く
		manager_.CangeScene(new MixGameClearScene(manager_));
		return;
	}
	// デバック用
//	DrawFormatString(0, 400, GetColor(255, 255, 255), "問題数:%d", answerNum);

	answerCheck = false;	// 正解のフラグの初期化

	// ランダムになっているか調べる(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "問題:% d", num);

	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// numと同じ方向が押されていたら次の問題へ
	// numが1キーの上が押されるまでfalse(待機)

	// ***通常問題***
	// 上が正解
	if (num == 1)
	{
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressUp();			// 誤答処理を呼び出す
		}
	}

	// 下が正解
	if (num == 2)
	{
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressDown();		// 誤答処理を呼び出す
		}
	}

	// 左が正解
	if (num == 3)
	{
		if (Pad::isTrigger(PAD_INPUT_LEFT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressLeft();		// 誤答処理を呼び出す
		}
	}

	// 右が正解
	if (num == 4)
	{
		if (Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressRight();		// 誤答処理を呼び出す
		}
	}

	// ***じゃない問題***

	// 上じゃない　(下左右ABXYが丸)
	if (num == 5)
	{
		if (Pad::isTrigger(PAD_INPUT_DOWN)  || Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT) || Pad::isTrigger(PAD_INPUT_1)    ||
			Pad::isTrigger(PAD_INPUT_2)     || Pad::isTrigger(PAD_INPUT_3)    ||
			Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressUp();		// 誤答処理を呼び出す
		}
	}

	//下じゃない　(上左右ABXYが丸)
	if (num == 6)
	{
		if (Pad::isTrigger(PAD_INPUT_UP)	|| Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT) || Pad::isTrigger(PAD_INPUT_1)    ||
			Pad::isTrigger(PAD_INPUT_2)		|| Pad::isTrigger(PAD_INPUT_3)    ||
			Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressDown();		// 誤答処理を呼び出す
		}
	}

	// 左じゃない　(上下右ABXYが丸)
	if (num == 7)
	{
		if (Pad::isTrigger(PAD_INPUT_UP)	|| Pad::isTrigger(PAD_INPUT_DOWN) ||
			Pad::isTrigger(PAD_INPUT_RIGHT) || Pad::isTrigger(PAD_INPUT_1)    ||
			Pad::isTrigger(PAD_INPUT_2)		|| Pad::isTrigger(PAD_INPUT_3)    ||
			Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressLeft();		// 誤答処理を呼び出す
		}
	}

	// 右じゃない　(上下左ABXYが丸)
	if (num == 8)
	{
		if (Pad::isTrigger(PAD_INPUT_UP)	|| Pad::isTrigger(PAD_INPUT_DOWN) ||
			Pad::isTrigger(PAD_INPUT_LEFT)  || Pad::isTrigger(PAD_INPUT_1)    ||
			Pad::isTrigger(PAD_INPUT_2)		|| Pad::isTrigger(PAD_INPUT_3)    ||
			Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressRight();		// 誤答処理を呼び出す
		}
	}

	// ***パッド通常問題***
	// Yが正解
	if (num == 9)
	{
		if (Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressY();			// 誤答処理を呼び出す
		}
	}

	// Aが正解
	if (num == 10)
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressA();		// 誤答処理を呼び出す
		}
	}

	// Xが正解
	if (num == 11)
	{
		if (Pad::isTrigger(PAD_INPUT_3))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressX();		// 誤答処理を呼び出す
		}
	}

	// Bが正解
	if (num == 12)
	{
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressB();		// 誤答処理を呼び出す
		}
	}

	// ***パッドじゃない問題***

	// Yじゃない　(ABX左右上下が丸)
	if (num == 13)
	{
		if (Pad::isTrigger(PAD_INPUT_1)    || Pad::isTrigger(PAD_INPUT_2)    ||
			Pad::isTrigger(PAD_INPUT_3)	   || Pad::isTrigger(PAD_INPUT_UP)   ||
			Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressY();		// 誤答処理を呼び出す
		}
	}

	//Aじゃない　(BXY左右上下が丸)
	if (num == 14)
	{
		if (Pad::isTrigger(PAD_INPUT_2)	   || Pad::isTrigger(PAD_INPUT_3)    ||
			Pad::isTrigger(PAD_INPUT_4)	   || Pad::isTrigger(PAD_INPUT_UP)   ||
			Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressA();		// 誤答処理を呼び出す
		}
	}

	// Xじゃない　(ABY左右上下が丸)
	if (num == 15)
	{
		if (Pad::isTrigger(PAD_INPUT_1)    || Pad::isTrigger(PAD_INPUT_2)    ||
			Pad::isTrigger(PAD_INPUT_4)	   || Pad::isTrigger(PAD_INPUT_UP)   ||
			Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressX();		// 誤答処理を呼び出す
		}
	}

	// Bじゃない　(AXY左右上下が丸)
	if (num == 16)
	{
		if (Pad::isTrigger(PAD_INPUT_1)    || Pad::isTrigger(PAD_INPUT_3)    ||
			Pad::isTrigger(PAD_INPUT_4)	   || Pad::isTrigger(PAD_INPUT_UP)   ||
			Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressX();		// 誤答処理を呼び出す
		}
	}

	// パッドのSTARTでポーズシーンへ
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}
}

void MixField::FadeOutUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
	}
}

void MixField::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void MixField::Draw()		// 問題の描画
{
	SetFontSize(50);
	DrawField();
	kMixTime.Draw();
	AnswerCheck();

	// 残り問題数を表示
	DrawFormatString(100, 190, GetColor(255, 255, 255), "問題数\n  %d", question);

	// 文字を拡大
	SetFontSize(100);

	// 問題
	switch (num)
	{
		// ***通常問題***

	case 1:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "上");
		break;

	case 2:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "下");
		break;

	case 3:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "左");
		break;

	case 4:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "右");
		break;

		// ***じゃない問題***

	case 5:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "上");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 6:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "下");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 7:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "左");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 8:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "右");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

		// ***パッド通常問題***

	case 9:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "Y");
		break;

	case 10:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "A");
		break;

	case 11:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "X");
		break;

	case 12:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "B");
		break;

		// ***パッドじゃない問題***

	case 13:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "Y");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 14:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "A");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 15:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "X");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 16:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "B");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;
	}

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MixField::DrawField()		// フィールドの描画
{
	// 背景描画
	DrawGraph(0, 0, handle, true);

	// フィールドの描画
	DrawBox(500, 150, 1100, 750, GetColor(0, 0, 0), true);
	DrawBox(500, 150, 1100, 750, GetColor(255, 255, 255), false);

	SetFontSize(100);
	DrawFormatString(750, 150, GetColor(225, 225, 225), "↑");

	DrawFormatString(750, 665, GetColor(225, 225, 225), "↓");

	DrawFormatString(1008, 400, GetColor(225, 225, 225), "→");

	DrawFormatString(492, 400, GetColor(225, 225, 225), "←");
}

// 不正解の場合の処理(通常ver)
void MixField::MissPressUp()	// 正解が上の場合
{
	if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT)|| Pad::isTrigger(PAD_INPUT_1)   ||
		Pad::isTrigger(PAD_INPUT_2)	   || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4) )
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressDown()	// 正解が下の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP)   || Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT)|| Pad::isTrigger(PAD_INPUT_1)   ||
		Pad::isTrigger(PAD_INPUT_2)    || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressLeft()	// 正解が左の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP)   || Pad::isTrigger(PAD_INPUT_DOWN)||
		Pad::isTrigger(PAD_INPUT_RIGHT)|| Pad::isTrigger(PAD_INPUT_1)   ||
		Pad::isTrigger(PAD_INPUT_2)    || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressRight()	// 正解が右の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP)  || Pad::isTrigger(PAD_INPUT_DOWN)||
		Pad::isTrigger(PAD_INPUT_LEFT)|| Pad::isTrigger(PAD_INPUT_1)   ||
		Pad::isTrigger(PAD_INPUT_2)   || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// 不正解の場合の処理(じゃないver)
void MixField::NotPressUp()	// 問題の答えが上以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressDown()	// 問題の答えが下以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressLeft()	// 問題の答えが左以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressRight()	// 問題の答えが右以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// パッド問題用不正解の場合の処理(通常ver)
void MixField::MissPressY()	// 正解がYの場合
{
	if (Pad::isTrigger(PAD_INPUT_1)   || Pad::isTrigger(PAD_INPUT_2)   ||
		Pad::isTrigger(PAD_INPUT_3)   || Pad::isTrigger(PAD_INPUT_UP)  ||
		Pad::isTrigger(PAD_INPUT_DOWN)|| Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressA()	// 正解がAの場合
{
	if (Pad::isTrigger(PAD_INPUT_2)   || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4)   || Pad::isTrigger(PAD_INPUT_UP)  ||
		Pad::isTrigger(PAD_INPUT_DOWN)|| Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressX()	// 正解がXの場合
{
	if (Pad::isTrigger(PAD_INPUT_1)   || Pad::isTrigger(PAD_INPUT_2)   ||
		Pad::isTrigger(PAD_INPUT_4)   || Pad::isTrigger(PAD_INPUT_UP)  ||
		Pad::isTrigger(PAD_INPUT_DOWN)|| Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressB()	// 正解がBの場合
{
	if (Pad::isTrigger(PAD_INPUT_1)   || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4)	  || Pad::isTrigger(PAD_INPUT_UP)  ||
		Pad::isTrigger(PAD_INPUT_DOWN)|| Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// パッド問題用不正解の場合の処理(じゃないver)
void MixField::NotPressY()	// 問題の答えがY以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressA()	// 問題の答えがA以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressX()	// 問題の答えがX以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressB()	// 問題の答えがA以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// タイムアップの場合の処理(即ゲームオーバー)
void MixField::TimeUp()
{
	manager_.CangeScene(new MixGameoverScene(manager_));
	return;
}

// 正解の入力
bool MixField::AnswerCheck()
{

	SetFontSize(50);

	// trueだったら正解正解ボタンが押されるまでは待機
	if (answerCheck == true)
	{
	//	DrawFormatString(0, 350, GetColor(255, 255, 255), "〇");
	}
	else
	{
	//	DrawFormatString(0, 300, GetColor(255, 255, 255), "待機中");
	}
	return false;
}

// 正解フラグ
bool MixField::AnswerFlag()
{
	if (answerCheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

