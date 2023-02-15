#pragma once
#include "Scene.h"
#include <memory>

class TimeBar;

/// <summary>
/// フィールド
/// </summary>
class KeyField : public Scene
{
public:

	KeyField(SceneManager& manager);
	~KeyField();

	void Init();
	void Update(const InputState& input);
	void Draw();
	void DrawField();

	// 不正解の場合	(通常ver)
	void MissPressUp();			// 正解が上の場合
	void MissPressDown();		// 正解が下の場合
	void MissPressLeft();		// 正解が左の場合
	void MissPressRight();		// 正解が右の場合

	// 不正解の場合	(じゃないver)
	void NotPressUp();			// 正解が上じゃない場合
	void NotPressDown();		// 正解が下じゃない場合
	void NotPressLeft();		// 正解が左じゃない場合
	void NotPressRight();		// 正解が右じゃない場合

	// タイムアップの場合の処理
	void TimeUp();

	// 正解が入力されたかどうかチェックする
	bool AnswerCheck();
	bool AnswerFlag();

private:

	unsigned int fadeColor = 0x1e90ff;	// フェードの色(デフォ黒)
	static constexpr int fadeInterval = 160;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// フェードイン時のUpdate関数
	void FadeInUpdate(const InputState& input);
	
	// 通常時のUpdate関数
	void NormalUpdate(const InputState& input);
	
	// フェードアウト時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(KeyField::*)(const InputState& input);
	UpdateFunc_t updateFunc = nullptr;

};



