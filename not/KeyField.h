#pragma once
#include "Scene.h"
#include <memory>

class TimeBar;

/// <summary>
/// �L�[���p�t�B�[���h
/// </summary>

class KeyField : public Scene
{
public:

	KeyField(SceneManager& manager);
	virtual ~KeyField();

	void Init();
	void Update(const InputState& input);
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

	// �^�C���A�b�v�̏ꍇ�̏���
	void TimeUp();

	// ���������͂��ꂽ���ǂ����`�F�b�N����
	bool AnswerCheck();
	bool AnswerFlag();

private:
	
	int num = 0;	// �����_���p

	int randomnum = 8;	// �S�̖̂��o���G�[�V������

	// ���̕����\���ʒu
	int mozi0X = 750;	// �ʏ�p
	int mozi0Y = 400;	// �ʏ�p

	int mozi1X = 750;	// ����Ȃ��p��s��
	int mozi1Y = 350;	// ����Ȃ��p��s��

	int mozi2X = 640;	// ����Ȃ��p��s��
	int mozi2Y = 450;	// ����Ȃ��p��s��


	int questionNum = 30;	// �����J��Ԃ���

	int question = 30;	// �\���p��萔
	
	int answerNum = 0;	// ���̐�����

	int handle = 0;	// �w�i�p�n���h��

	int buttonSTARThandle = 0;	// �|�[�Y�摜�p�n���h��

	int musicGameScene = 0;	// �Q�[����BGM�n���h��
	int seButtonYes = 0;	// �����Ƃ���SE�n���h��
	int seButtonNo = 0;		// �s�����Ƃ���SE�n���h��
	int seButtonPause = 0;	// �|�[�Y�V�[���ֈڍs����Ƃ���SE�n���h��

	int countDown = 180;	// ���\���p�J�E���g�_�E��
	int countNum = 3;


	unsigned int fadeColor = 0x1e90ff;	// �t�F�[�h�̐F(�f�t�H��)
	static constexpr int fadeInterval = 60;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;
	
	// �J�E���g�_�E���p�A�b�v�f�[�g�֐�
	void CountDownUpdate();

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);
	
	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);
	
	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(KeyField::*)(const InputState& input);
	UpdateFunc_t updateFunc = nullptr;

};



