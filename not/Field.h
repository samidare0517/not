#pragma once
class TimeBar;

class Field
{
public:
	Field();
	~Field();

	void Init();
	void Update();
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

	// ゲームが終了しているか続行しているか調べる
//	bool isGameEnd();

private:

};



