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

	// 不正解の場合
	void MissPressUp();
	void MissPressDown();
	void MissPressLeft();
	void MissPressRight();


	// 正解が入力されたかどうかチェックする
	bool AnswerCheck();
	bool AnswerFlag();

	// ゲームが終了しているか続行しているか調べる
//	bool isGameEnd();

private:

};



