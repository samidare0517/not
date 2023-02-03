#include "Field.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "GameoverScene.h"
#include "PauseScene.h"
#include "DxLib.h"
#include "Pad.h"
#include <time.h>		// ランダム用
#include"TimeBar.h"

namespace
{
	// ランダム用
	int num = 0;

	// 全体の問題バリエーション数
	int randomnum = 8;

	// 問題の文字表示位置
	int moziX = 400;
	int moziY = 400;

	bool answercheck = false;

	// 問題を繰り返す回数
	int questionnum = 30;
	int i = 0;

	TimeBar kTime;
}

void Field::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 225 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &Field::NormalUpdate;
	}
}

Field::Field(SceneManager& manager) :Scene(manager),
updateFunc_(&Field::FadeInUpdate)
{
	Init();
}

Field::~Field()
{
}

void Field::Init()
{
	kTime.Init();
	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	num = rand() % randomnum + 1;		// 1～4の乱数を出す
}

void Field::NormalUpdate(const InputState& input)
{
	Pad::update();
	kTime.Update();

	if (answercheck == true)	// 正解が押されたら次の問題へ
	{
		for (int i = 0; i < questionnum; i++)		// 20問繰り返す
		{
			num = rand() % randomnum + 1;
		}
		i++;

	}
	SetFontSize(50);
	// 確認用
	if (i == 30)
	{
	
		DrawFormatString(0, 350, GetColor(255, 255, 255), "全問正解:% d", i);
	}
	
	DrawFormatString(0, 300, GetColor(255, 255, 255), "問題数:% d", i);

	answercheck = false;	// 正解のフラグの初期化

	
	
	// ランダムになっているか調べる(デバック用)

	DrawFormatString(0, 100, GetColor(255, 255, 255), "問題:% d", num);

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
			answercheck = true;		// 正解が押されたらマル
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
			answercheck = true;		// 正解が押されたらマル
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
			answercheck = true;		// 正解が押されたらマル
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
			answercheck = true;		// 正解が押されたらマル
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
			answercheck = true;		// 正解が押されたらマル
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
			answercheck = true;		// 正解が押されたらマル
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
			answercheck = true;		// 正解が押されたらマル
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
			answercheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressRight();		// 誤答処理を呼び出す
		}
	}


	if (input.IsTriggred(InputType::next))
	{
		updateFunc_ = &Field::FadeOutUpdate;
		fadeColor_ = 0x000000;
	}
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}

}

void Field::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 225 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (++fadeTimer_ == fade_interval)
	{
		manager_.CangeScene(new GameoverScene(manager_));
		return;
	}
}

void Field::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void Field::Draw()		// 問題の描画
{
	SetFontSize(50);
	DrawField();
	kTime.Draw();
	AnswerCheck();

	SetFontSize(100);
	// 文字を拡大
	switch (num)	// 問題
	{
		// ***通常問題***

	case 1:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "上");
		break;

	case 2:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "下");
		break;

	case 3:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "左");
		break;

	case 4:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "右");
		break;

		// ***じゃない問題***

	case 5:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "上");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "じゃない");
		break;
	
	case 6:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "下");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "じゃない");
		break;
	
	case 7:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "左");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "じゃない");
		break;

	case 8:
		// 表示する文字
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "右");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "じゃない");
		break;
	}

	// 今から各画像とすでに描画されているスクリーンとのブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);

	// 画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, 900, 900, GetColor(255, 255, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Field::DrawField()		// フィールドの描画
{
	SetFontSize(100);
	DrawFormatString(400, 150, GetColor(225, 225, 225), "↑");

	DrawFormatString(400, 650, GetColor(225, 225, 225), "↓");

	DrawFormatString(650, 400, GetColor(225, 225, 225), "→");

	DrawFormatString(150, 400, GetColor(225, 225, 225), "←");

	// フィールドの描画
	DrawBox(150, 150, 750, 750, GetColor(255, 225, 255), false);
}

// 不正解の場合の処理(通常ver)

void Field::MissPressUp()	// 正解が上の場合
{
	if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::MissPressDown()	// 正解が下の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_LEFT) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::MissPressLeft()	// 正解が左の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::MissPressRight()	// 正解が右の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
		Pad::isTrigger(PAD_INPUT_LEFT))
	{
	//	gameend = true;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// 不正解の場合の処理(じゃないver)

void Field::NotPressUp()	// 問題の答えが上以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::NotPressDown()	// 問題の答えが下以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::NotPressLeft()	// 問題の答えが左以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void Field::NotPressRight()	// 問題の答えが右以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
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

bool Field::AnswerFlag()
{
	if (answercheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

