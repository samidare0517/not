#pragma once
#include "Scene.h"
#include <memory>

class TimeBar;

class Field : public Scene
{
public:
	Field(SceneManager& manager);
	~Field();

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


	// 正解が入力されたかどうかチェックする
	bool AnswerCheck();
	bool AnswerFlag();


private:
	unsigned int fadeColor_ = 0x000000;	// フェードの色(デフォ黒)
	
	static constexpr int fade_interval = 60;

	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(Field::*)(const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

};



