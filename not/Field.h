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


private:
	unsigned int fadeColor_ = 0x000000;	// �t�F�[�h�̐F(�f�t�H��)
	
	static constexpr int fade_interval = 60;

	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(Field::*)(const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

};



