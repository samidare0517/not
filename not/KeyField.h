#pragma once
#include "Scene.h"
#include <memory>

class TimeBar;

/// <summary>
/// �t�B�[���h
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

	using UpdateFunc_t = void(KeyField::*)(const InputState& input);
	UpdateFunc_t updateFunc = nullptr;

};



