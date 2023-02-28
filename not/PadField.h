#pragma once
#include "Scene.h"
#include <memory>

class TimeBar;

/// <summary>
/// �p�b�h���p�t�B�[���h
/// </summary>

class PadField : public Scene
{
public:

	PadField(SceneManager& manager);
	~PadField();

	void Init();
	void Update(const InputState& input);
	void Draw();
	void DrawField();

	// �s�����̏ꍇ	(�ʏ�ver)
	void MissPressY();		// ��������̏ꍇ
	void MissPressA();		// ���������̏ꍇ
	void MissPressX();		// ���������̏ꍇ
	void MissPressB();		// �������E�̏ꍇ

	// �s�����̏ꍇ	(����Ȃ�ver)
	void NotPressY();		// �������ザ��Ȃ��ꍇ
	void NotPressA();		// ������������Ȃ��ꍇ
	void NotPressX();		// ������������Ȃ��ꍇ
	void NotPressB();		// �������E����Ȃ��ꍇ

	// �^�C���A�b�v�̏ꍇ�̏���
	void TimeUp();

	// ���������͂��ꂽ���ǂ����`�F�b�N����
	bool AnswerCheck();
	bool AnswerFlag();

private:

	unsigned int fadeColor = 0x1e90ff;	// �t�F�[�h�̐F(�f�t�H��)
	static constexpr int fadeInterval = 160;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(PadField::*)(const InputState& input);
	UpdateFunc_t updateFunc = nullptr;

};



