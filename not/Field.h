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

	// �s�����̏ꍇ	(�ʏ�ver)
	void MissPressUp();			// ��������̏ꍇ
	void MissPressDown();		// ���������̏ꍇ
	void MissPressLeft();		// ���������̏ꍇ
	void MissPressRight();		// �������E�̏ꍇ

	// �s�����̏ꍇ	(����Ȃ�ver)
	void NotPressUp();			// �������ザ��Ȃ��ꍇ
	void NotPressDown();		// ������������Ȃ��ꍇ
	void NotPressLeft();		// ������������Ȃ��ꍇ
	void NotPressRight();		// �������E����Ȃ��ꍇ


	// ���������͂��ꂽ���ǂ����`�F�b�N����
	bool AnswerCheck();
	bool AnswerFlag();

	// �Q�[�����I�����Ă��邩���s���Ă��邩���ׂ�
//	bool isGameEnd();

private:

};



