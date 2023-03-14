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
	bool answerCheck = false;
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
	// 画像のデリート
	DeleteGraph(handle);
	DeleteGraph(maruHandle);
	DeleteGraph(batuHandle);
	DeleteGraph(buttonSTARThandle);

	// 音楽のデリート
	DeleteSoundMem(musicGameScene);
	DeleteSoundMem(seButtonYes);
	DeleteSoundMem(seButtonNo);
	DeleteSoundMem(seButtonPause);
}

void MixField::Init()
{
	handle = LoadGraph("data/Back.png");	// タイムバー用画像
	
	maruHandle = LoadGraph("data/maru.png");	// 正解用マル画像

	batuHandle = LoadGraph("data/batu.png");	// 正解用バツ画像

	buttonSTARThandle = LoadGraph("data/button/buttonSTART.png");	// ポーズボタン用画像

	// BGMの読みこみ
	musicGameScene = LoadSoundMem("data/BGM/GameSceneBGM.mp3");

	// BGMの音量を調整する
	ChangeVolumeSoundMem(255 * 30 / 100, musicGameScene);

	// BGMを呼び出す
	PlaySoundMem(musicGameScene, DX_PLAYTYPE_LOOP, false);

	kMixTime.Init();

	answerNum = 0;	// 問題の正解数カウントを0にする(初期化)

	question = 30;	// 残り問題数を初期化

	srand((unsigned int)time(NULL));	// 現在時刻の情報で初期化
	num = rand() % randomnum + 1;		// 1～8の乱数を出す
}

void MixField::NormalUpdate(const InputState& input)
{
	Pad::Update();
	if (countDown == 0)	// カウントダウンが0になったらkTime.Updateを呼び出す
	{
		kMixTime.Update();
	}
	CountDownUpdate();

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
	if (answerNum == 5)
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

	if (countDown == 0)	// カウントが0になったら入力を受け付ける
	{
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
			if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
				Pad::isTrigger(PAD_INPUT_RIGHT) || Pad::isTrigger(PAD_INPUT_1) ||
				Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
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
			if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_LEFT) ||
				Pad::isTrigger(PAD_INPUT_RIGHT) || Pad::isTrigger(PAD_INPUT_1) ||
				Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
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
			if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
				Pad::isTrigger(PAD_INPUT_RIGHT) || Pad::isTrigger(PAD_INPUT_1) ||
				Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
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
			if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
				Pad::isTrigger(PAD_INPUT_LEFT) || Pad::isTrigger(PAD_INPUT_1) ||
				Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
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
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
				Pad::isTrigger(PAD_INPUT_3) || Pad::isTrigger(PAD_INPUT_UP) ||
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
			if (Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
				Pad::isTrigger(PAD_INPUT_4) || Pad::isTrigger(PAD_INPUT_UP) ||
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
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
				Pad::isTrigger(PAD_INPUT_4) || Pad::isTrigger(PAD_INPUT_UP) ||
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
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_3) ||
				Pad::isTrigger(PAD_INPUT_4) || Pad::isTrigger(PAD_INPUT_UP) ||
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
	}

	// パッドのSTARTでポーズシーンへ
	if (input.IsTriggred(InputType::pause))
	{
		// ポーズシーンへの移行用のSEの読み込み
		seButtonPause = LoadSoundMem("data/BGM/PauseSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 150 / 100, seButtonPause);

		// SEを呼び出す
		PlaySoundMem(seButtonPause, DX_PLAYTYPE_BACK, false);
		manager_.PushScene(new PauseScene(manager_));
	}
}

void MixField::CountDownUpdate()
{
	if (fadeTimer == 0)
	{
		countDown--;	// フェードタイマーが0になったら(フェードが終わり次第)カウントダウンをする
	}
	if (countDown < 0)
	{
		countDown = 0;
	}
	countNum = (countDown / 60);	// 180/60で3，2，1カウントをする
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
	SetFontSize(40);
	DrawFormatString(960, 170, GetColor(255, 255, 255), "問題数\n  %d", question);
	
	// ポーズ案内表示
	SetFontSize(20);
	DrawFormatString(900, 720, GetColor(255, 255, 255), "ポーズ ・・・");
	DrawGraph(1000, 695, buttonSTARThandle, true);
	
	SetFontSize(50);

	// 文字を拡大
	SetFontSize(100);

	if (countNum != 0)	// countNumが0ではなかったら数字を減らしながら表示する
	{
		SetFontSize(200);
		ChangeFont("Franklin Gothic Medium");	// Franklin Gothic Mediumに変更
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント

		DrawFormatString(740, 350, GetColor(255, 255, 127), "%d", countNum);

		ChangeFont("UD デジタル 教科書体 NK-B");	// UD デジタル 教科書体 NK-Bに変更
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// アンチエイリアスフォント
	}
	if (countDown == 0)	// カウントが0になったら問題を表示
	{
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
			DrawFormatString(mozi3X, mozi3Y, GetColor(255, 255, 255), "Y");
			break;

		case 10:
			// 表示する文字
			DrawFormatString(mozi3X, mozi3Y, GetColor(255, 255, 255), "A");
			break;

		case 11:
			// 表示する文字
			DrawFormatString(mozi3X, mozi3Y, GetColor(255, 255, 255), "X");
			break;

		case 12:
			// 表示する文字
			DrawFormatString(mozi3X, mozi3Y, GetColor(255, 255, 255), "B");
			break;

			// ***パッドじゃない問題***

		case 13:
			// 表示する文字
			DrawFormatString(mozi4X, mozi4Y, GetColor(255, 255, 255), "Y");
			DrawFormatString(mozi5X, mozi5Y, GetColor(255, 255, 255), "じゃない");
			break;

		case 14:
			// 表示する文字
			DrawFormatString(mozi4X, mozi4Y, GetColor(255, 255, 255), "A");
			DrawFormatString(mozi5X, mozi5Y, GetColor(255, 255, 255), "じゃない");
			break;

		case 15:
			// 表示する文字
			DrawFormatString(mozi4X, mozi4Y, GetColor(255, 255, 255), "X");
			DrawFormatString(mozi5X, mozi5Y, GetColor(255, 255, 255), "じゃない");
			break;

		case 16:
			// 表示する文字
			DrawFormatString(mozi4X, mozi4Y, GetColor(255, 255, 255), "B");
			DrawFormatString(mozi5X, mozi5Y, GetColor(255, 255, 255), "じゃない");
			break;
		}
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
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressDown()// 正解が下の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP)   || Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT)|| Pad::isTrigger(PAD_INPUT_1)   ||
		Pad::isTrigger(PAD_INPUT_2)    || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressLeft()	// 正解が左の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP)   || Pad::isTrigger(PAD_INPUT_DOWN)||
		Pad::isTrigger(PAD_INPUT_RIGHT)|| Pad::isTrigger(PAD_INPUT_1)   ||
		Pad::isTrigger(PAD_INPUT_2)    || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressRight()	// 正解が右の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP)  || Pad::isTrigger(PAD_INPUT_DOWN)||
		Pad::isTrigger(PAD_INPUT_LEFT)|| Pad::isTrigger(PAD_INPUT_1)   ||
		Pad::isTrigger(PAD_INPUT_2)   || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// 不正解の場合の処理(じゃないver)
void MixField::NotPressUp()	// 問題の答えが上以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressDown()	// 問題の答えが下以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressLeft()	// 問題の答えが左以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);
		
		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressRight()	// 問題の答えが右以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
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
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressA()	// 正解がAの場合
{
	if (Pad::isTrigger(PAD_INPUT_2)   || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4)   || Pad::isTrigger(PAD_INPUT_UP)  ||
		Pad::isTrigger(PAD_INPUT_DOWN)|| Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressX()	// 正解がXの場合
{
	if (Pad::isTrigger(PAD_INPUT_1)   || Pad::isTrigger(PAD_INPUT_2)   ||
		Pad::isTrigger(PAD_INPUT_4)   || Pad::isTrigger(PAD_INPUT_UP)  ||
		Pad::isTrigger(PAD_INPUT_DOWN)|| Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::MissPressB()	// 正解がBの場合
{
	if (Pad::isTrigger(PAD_INPUT_1)   || Pad::isTrigger(PAD_INPUT_3)   ||
		Pad::isTrigger(PAD_INPUT_4)	  || Pad::isTrigger(PAD_INPUT_UP)  ||
		Pad::isTrigger(PAD_INPUT_DOWN)|| Pad::isTrigger(PAD_INPUT_LEFT)||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);
		
		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// パッド問題用不正解の場合の処理(じゃないver)
void MixField::NotPressY()	// 問題の答えがY以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressA()	// 問題の答えがA以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressX()	// 問題の答えがX以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

void MixField::NotPressB()	// 問題の答えがA以外の場合
{
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		// 不正解用SEの読み込み
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SEを呼び出す
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// 不正解用バツ画像表示
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new MixGameoverScene(manager_));
		return;
		// デバック用
		//DrawFormatString(0, 220, GetColor(255, 255, 255), "×");
	}
}

// タイムアップの場合の処理(即ゲームオーバー)
void MixField::TimeUp()
{
	// 不正解用SEの読み込み
	seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

	// SEの音量を調整する
	ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

	// SEを呼び出す
	PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

	updateFunc = &MixField::FadeOutUpdate;
}

// 正解の入力
bool MixField::AnswerCheck()
{

	SetFontSize(50);

	// trueだったら正解正解ボタンが押されるまでは待機
	if (answerCheck == true)
	{
		// 正解用SEの読みこみ
		seButtonYes = LoadSoundMem("data/BGM/SeikaiSE.mp3");

		// SEの音量を調整する
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonYes);

		// SEを呼び出す
		PlaySoundMem(seButtonYes, DX_PLAYTYPE_BACK, false);

		// 正解用マル画像
		DrawGraph(900, 550, maruHandle, true);

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

