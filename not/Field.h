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

	// �s�����̏ꍇ
	void MissPressUp();
	void MissPressDown();
	void MissPressLeft();
	void MissPressRight();


	// ���������͂��ꂽ���ǂ����`�F�b�N����
	bool AnswerCheck();
	bool AnswerFlag();

	// �Q�[�����I�����Ă��邩���s���Ă��邩���ׂ�
//	bool isGameEnd();

private:

};



