#include "Field.h"
#include "DxLib.h"
#include "Pad.h"
#include <time.h>		// ランダム用
#include"TimeBar.h"

namespace
{
	// ランダム用
	int num = 0;

	// 問題数
	int randomnum = 4;

	// 問題の文字表示位置
	int moziX = 350;
	int moziY = 350;

	//bool gameend = false;
	bool answercheck = false;


	// 問題を繰り返す回数
	int questionnum = 20;
	int i = 0;

	TimeBar kTime;
}


Field::Field() 
{

}

Field::~Field()
{

}

void Field::Init()
{
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化

	num = rand() % randomnum + 1;		// 1～4の乱数を出す
}

void Field::Update()
{

	answercheck = false;	// 正解のフラグの初期化
	

	if (kTime.Check() == true)	// フラグがtrueだったらランダムに問題を出す
	{
		num = rand() % randomnum + 1;
	}



	for (i = 0; i < questionnum; i++);
	DrawFormatString(0, 260, GetColor(255, 255, 255), "繰り返し数:% d", i);
	
	
	// ランダムになっているか調べる(デバック用)
	DrawFormatString(0, 100, GetColor(255, 255, 255), "問題:% d", num);

	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// numと同じ方向が押されていたら次の問題へ

	// numが1キーの上が押されるまでfalse(待機)
	if (num == 1)
	{
		if (padState & (PAD_INPUT_UP))
		{
			answercheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressUp();			// 誤答処理を呼び出す
		}
		
	}

	if (num == 2)
	{
		if (padState & (PAD_INPUT_DOWN))
		{
			answercheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressDown();		// 誤答処理を呼び出す
		}
	}

	if (num == 3)
	{
		if (padState & (PAD_INPUT_RIGHT))
		{
			answercheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressRight();		// 誤答処理を呼び出す
		}
	}

	if (num == 4)
	{
		if (padState & (PAD_INPUT_LEFT))
		{
			answercheck = true;		// 正解が押されたらマル
		}
		else
		{
			MissPressLeft();		// 誤答処理を呼び出す
		}
	}


	// 「じゃない」テスト
	//if (num == 5)
	//{
	//	if (padState & (PAD_INPUT_LEFT))
	//	{
	//		answercheck = false;		// 正解が押されたらマル
	//	}
	//	else
	//	{
	//		answercheck = true;
	//	}
	//}

}

void Field::Draw()		// 問題の描画
{

	// 文字を拡大
	SetFontSize(100);
	switch (num)	// 問題
	{
	case 1:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "上");
		break;

	case 2:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "下");
		break;

	case 3:;
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "右");
		break;

	case 4:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "左");
		break;

	//case 5:
	//	// 表示する文字
	//	DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "左");
	//	DrawFormatString(200, 500, GetColor(255, 255, 255), "じゃない");
	//	break;
	

	default:
		break;
	}
}

void Field::DrawField()		// フィールドの描画
{

	DrawFormatString(350, 100, GetColor(225, 225, 225), "↑");

	DrawFormatString(350, 600, GetColor(225, 225, 225), "↓");

	DrawFormatString(600, 350, GetColor(225, 225, 225), "→");

	DrawFormatString(100, 350, GetColor(225, 225, 225), "←");

	// フィールドの描画
	DrawBox(100, 100, 700, 700, GetColor(255, 255, 255), false);

}

// 不正解の場合の処理
void Field::MissPressUp()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_DOWN) || padState & (PAD_INPUT_LEFT) ||
		padState & (PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::MissPressDown()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_UP) || padState & (PAD_INPUT_LEFT) ||
		padState & (PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::MissPressLeft()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_UP) || padState & (PAD_INPUT_DOWN) ||
		padState & (PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::MissPressRight()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_UP) || padState & (PAD_INPUT_DOWN) ||
		padState & (PAD_INPUT_LEFT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// 正解の入力
bool Field::AnswerCheck()
{

	SetFontSize(50);
	
	// trueだったら正解正解ボタンが押されるまでは待機
	if (answercheck == true)
	{
		DrawFormatString(0, 200, GetColor(255, 255, 255), "〇");
	}
	else
	{
		DrawFormatString(0, 150, GetColor(255, 255, 255), "待機中");
	}
	return false;
}



// ゲームが終了しているか続行しているか調べる
//bool Field::isGameEnd()
//{
//	SetFontSize(50);
//
//	if(gameend == true)
//	{
//		// エンドシーンへ行く
//		DrawFormatString(0, 200, GetColor(255, 255, 255), "終了");
//	}
//	else
//	{
//		// ゲーム続行
//		DrawFormatString(0, 200, GetColor(255, 255, 255), "続行");
//	}
//	return false;
//}