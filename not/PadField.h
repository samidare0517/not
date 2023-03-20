#pragma once
#include "Scene.h"
#include <memory>

class TimeBar;

/// <summary>
/// パッド問題用フィールド
/// </summary>

class PadField : public Scene
{
public:

	PadField(SceneManager& manager);
	virtual ~PadField();

	void Update(const InputState& input);
	void Draw();
	void DrawField();

	// 不正解の場合	(通常ver)
	void MissPressY();		// 正解が上の場合
	void MissPressA();		// 正解が下の場合
	void MissPressX();		// 正解が左の場合
	void MissPressB();		// 正解が右の場合

	// 不正解の場合	(じゃないver)
	void NotPressY();		// 正解が上じゃない場合
	void NotPressA();		// 正解が下じゃない場合
	void NotPressX();		// 正解が左じゃない場合
	void NotPressB();		// 正解が右じゃない場合

	// タイムアップの場合の処理
	void TimeUp();

	// 正解が入力されたかどうかチェックする
	bool AnswerCheck();
	bool AnswerFlag();

private:

	int num = 0;	// ランダム用

	int randomnum = 8;	// 全体の問題バリエーション数

	// 問題の文字表示位置
	int mozi0X = 765;	// 通常用(ABXY)
	int mozi0Y = 400;	// 通常用(ABXY)

	int mozi1X = 765;	// じゃない用一行目(ABXY)
	int mozi1Y = 350;	// じゃない用一行目(ABXY)

	int mozi2X = 640;	// じゃない用二行目(ABXY)
	int mozi2Y = 450;	// じゃない用二行目(ABXY)


	int questionNum = 20;	// 問題を繰り返す回数

	int question = 20;	// 表示用問題数

	int answerNum = 0;	// 問題の正解回数

	int handle = 0;	// 背景用ハンドル

	int maruHandle = 0;	// 正解用マル画像表示

	int batuHandle = 0;	// 不正解用バツ画像表示

	int buttonSTARThandle = 0;	// ポーズ画像用ハンドル

	int musicGameScene = 0;	// ゲーム中BGMハンドル
	int seButtonYes = 0;	// 正解ときのSEハンドル
	int seButtonNo = 0;		// 不正解ときのSEハンドル
	int seButtonPause = 0;	// ポーズシーンへ移行するときのSEハンドル

	int countDown = 180;	// 問題表示用カウントダウン
	int countNum = 3;

	unsigned int fadeColor = 0x1e90ff;	// フェードの色(デフォ黒)
	static constexpr int fadeInterval = 60;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// カウントダウン用アップデート関数
	void CountDownUpdate();

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);

	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);

	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(PadField::*)(const InputState& input);
	UpdateFunc_t updateFunc = nullptr;

};



