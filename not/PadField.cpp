#include "PadField.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PadGameoverScene.h"
#include "PadGameClearScene.h"
#include "PauseScene.h"
#include "DxLib.h"
#include "Pad.h"
#include <time.h>		// ランダム用
#include"TimeBar.h"

namespace
{
	TimeBar kMixTime;
}

void PadField::FadeInUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &PadField::NormalUpdate;
	}
}

PadField::PadField(SceneManager& manager) :Scene(manager),
updateFunc(&PadField::FadeInUpdate)
{
	Init();
}

PadField::~PadField()
{
	// 画像のデリート
	DeleteGraph(handle);

	// 音楽のデリート
	DeleteSoundMem(musicGameScene);
	DeleteSoundMem(seButtonYse);
	DeleteSoundMem(seButtonNo);
}

void PadField::Init()
{
	handle = LoadGraph("data/Back.png");	// タイムバー用画像

	// BGMの読みこみ
	musicGameScene = LoadSoundMem("data/BGM/GameSceneBGM.mp3");

	// BGMの音量を調整する
	ChangeVolumeSoundMem(255 * 30 / 100, musicGameScene);

	// BGMを呼び出す
	PlaySoundMem(musicGameScene, DX_PLAYTYPE_LOOP, false);

	// 正解用SEの読みこみ
	seButtonYse = LoadSoundMem("data/BGM/SeikaiBGM.mp3");

	// 不正解用SEの読み込み
	seButtonYse = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

	kMixTime.Init();

	answerNum = 0;	// 問題の正解数カウントを0にする(初期化)

	question = 30;	// 残り問題数を初期化

	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	num = rand() % randomnum + 1;		// 1～8の乱数を出す
}

void PadField::NormalUpdate(const InputState& input)
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
	if (answerNum == 1)
	{
		answerCheck = false;	// 正解のフラグの初期化

		// 指定の回数正解したらゲームクリアシーンに行く
		manager_.CangeScene(new PadGameClearScene(manager_));
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
	// Yが正解
	if (num == 1)
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
	if (num == 2)
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
	if (num == 3)
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
	if (num == 4)
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

	// ***じゃない問題***

	// Yじゃない　(ABXが丸)
	if (num == 5)
	{
		if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
			Pad::isTrigger(PAD_INPUT_3))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressY();		// 誤答処理を呼び出す
		}
	}

	//Aじゃない　(BXYが丸)
	if (num == 6)
	{
		if (Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
			Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressA();		// 誤答処理を呼び出す
		}
	}

	// Xじゃない　(ABYが丸)
	if (num == 7)
	{
		if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
			Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressX();		// 誤答処理を呼び出す
		}
	}

	// Bじゃない　(AXYが丸)
	if (num == 8)
	{
		if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_3) ||
			Pad::isTrigger(PAD_INPUT_4))
		{
			answerCheck = true;		// 正解が押されたらマル
		}
		else
		{
			NotPressB();		// 誤答処理を呼び出す
		}
	}


	// Pキーでポーズシーン
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}
}

void PadField::FadeOutUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
	}
}

void PadField::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void PadField::Draw()		// 問題の描画
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
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "Y");
		break;

	case 2:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "A");
		break;

	case 3:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "X");
		break;

	case 4:
		// 表示する文字
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "B");
		break;

		// ***じゃない問題***

	case 5:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "Y");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 6:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "A");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 7:
		// 表示する文字
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "X");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "じゃない");
		break;

	case 8:
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

void PadField::DrawField()		// フィールドの描画
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
void PadField::MissPressY()	// 正解がYの場合
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
		Pad::isTrigger(PAD_INPUT_3))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void PadField::MissPressA()	// 正解がAの場合
{
	if (Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void PadField::MissPressX()	// 正解がXの場合
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void PadField::MissPressB()	// 正解がBの場合
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_3) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// 不正解の場合の処理(じゃないver)
void PadField::NotPressY()	// 問題の答えがY以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void PadField::NotPressA()	// 問題の答えがA以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void PadField::NotPressX()	// 問題の答えがX以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void PadField::NotPressB()	// 問題の答えがA以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// デバック用
		DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// タイムアップの場合の処理(即ゲームオーバー)
void PadField::TimeUp()
{
	manager_.CangeScene(new PadGameoverScene(manager_));
	return;
}

// 正解の入力
bool PadField::AnswerCheck()
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

bool PadField::AnswerFlag()
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

