#include "KeyField.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "KeyGameoverScene.h"
#include "KeyGameClearScene.h"
#include "PauseScene.h"
#include "DxLib.h"
#include "Pad.h"
#include <time.h>		// ランダム用
#include "TimeBar.h"

namespace
{
	// ランダム用
	int num = 0;

	// 全体の問題バリエーション数
	int randomnum = 8;

	// 問題の文字表示位置
	int mozi0X = 750;	// 通常用
	int mozi0Y = 400;	// 通常用

	int mozi1X = 750;	// じゃない用一行目
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

	TimeBar kTime;
}

void KeyField::FadeInUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &KeyField::NormalUpdate;
	}
}

KeyField::KeyField(SceneManager& manager) :Scene(manager),
updateFunc(&KeyField::FadeInUpdate)
{
	Init();
}

KeyField::~KeyField()
{
}

void KeyField::Init()
{
	handle = LoadGraph("data/Back.png");	// タイムバー用画像

	kTime.Init();

 	answerNum = 0;	// 問題の正解数カウントを0にする(初期化)

	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	num = rand() % randomnum + 1;		// 1～8の乱数を出す
}

void KeyField::NormalUpdate(const InputState& input)
{

	// 背景描画 (デバック文字が見えるように背景を表示)
//	DrawGraph(0, 0, handle, true);

	Pad::Update();
	kTime.Update();

	if (answerCheck == true)	// 正解が押されたら次の問題へ
	{
		for (int i = 0; i < questionNum; i++)		// 30問繰り返す
		{
			num = rand() % randomnum + 1;
		}
		answerNum++;
		question--;
	}
	else if (kTime.Check() == true)	// タイムバーが0になっていたらゲームオーバー処理へ
	{
		TimeUp();
	}

	// 正解数が30になったらクリア画面へ
	SetFontSize(50);
	if (answerNum == 30)
	{
		answerCheck = false;	// 正解のフラグの初期化

		// 指定の回数正解したらゲームクリアシーンに行く
		manager_.CangeScene(new KeyGameClearScene(manager_));
		return;	
	}
	// デバック用
//	DrawFormatString(0, 400, GetColor(255, 255, 255), "問題数:%d", answerNum);

	answerCheck = false;	// 正解のフラグの初期化

	// ランダムになっているか調べる(デバック用)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "問題:% d", num);

	
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
	
	// 上じゃない　(下左右が丸)
	if (num == 5)
	{
		if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) || 
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressUp();		// 誤答処理を呼び出す
		}
	}

	 //下じゃない　(上左右が丸)
	if (num == 6)
	{
		if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressDown();		// 誤答処理を呼び出す
		}
	}

	// 左じゃない　(上下右が丸)
	if (num == 7)
	{
		if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressLeft();		// 誤答処理を呼び出す
		}
	}

	// 右じゃない　(上下左が丸)
	if (num == 8)
	{
		if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
			Pad::isTrigger(PAD_INPUT_LEFT))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressRight();		// 誤答処理を呼び出す
		}
	}

	
	// パッドのSTARTでポーズシーン
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}
}

void KeyField::FadeOutUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
	}
}

void KeyField::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void KeyField::Draw()		// 問題の描画
{
	SetFontSize(50);
	DrawField();
	kTime.Draw();
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
	}

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// 画面全体を黒に塗りつぶす
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void KeyField::DrawField()		// フィールドの描画
{
	// 背景描画
	DrawGraph(0, 0, handle, true);

	// フィールドの描画
	DrawBox(500, 150, 1100, 750, GetColor(0, 0, 0), true);
	DrawBox(500, 150, 1100, 750, GetColor(255, 255, 255), false);

	SetFontSize(100);
	DrawFormatString(750,  150, GetColor(225, 225, 225), "↑");

	DrawFormatString(750,  665, GetColor(225, 225, 225), "↓");

	DrawFormatString(1008, 400, GetColor(225, 225, 225), "→");

	DrawFormatString(492,  400, GetColor(225, 225, 225), "←");
}

// 不正解の場合の処理(通常ver)
void KeyField::MissPressUp()	// 正解が上の場合
{
	if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");	
	}
}

void KeyField::MissPressDown()	// 正解が下の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_LEFT) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void KeyField::MissPressLeft()	// 正解が左の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void KeyField::MissPressRight()	// 正解が右の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
		Pad::isTrigger(PAD_INPUT_LEFT))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// 不正解の場合の処理(じゃないver)
void KeyField::NotPressUp()	// 問題の答えが上以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void KeyField::NotPressDown()	// 問題の答えが下以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void KeyField::NotPressLeft()	// 問題の答えが左以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void KeyField::NotPressRight()	// 問題の答えが右以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		manager_.CangeScene(new KeyGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// タイムアップの場合の処理(即ゲームオーバー)
void KeyField::TimeUp()
{
	manager_.CangeScene(new KeyGameoverScene(manager_));
	return;
}

// 正解の入力
bool KeyField::AnswerCheck()
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
bool KeyField::AnswerFlag()
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

