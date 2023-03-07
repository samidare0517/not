#pragma once
#include "Scene.h"

class InputState;

/// <summary>
/// �Q�[���S�̐���
/// </summary>

class GameExplanation : public Scene
{
public:

	GameExplanation(SceneManager& manager);
	~GameExplanation();

	void Update(const InputState& input);

	void Draw();

private:

	int explanationHandle = -1;		// �^�C�g���摜
	int buttonRBhandle = -1;	// RB�{�^���摜
	int musicTitle = 0;	// �^�C�g��BGM�n���h��
	int seButton = 0;	// ���ɍs���Ƃ���SE�n���h��

	static constexpr int fadeIntarval = 60;
	int fadeTimer = fadeIntarval;		// �t�F�[�h�^�C�}�[
	int fadeValue = 225;	// ����`�Ƃ̃u�����h�

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	// Update�p�����o�֐��|�C���^
	void (GameExplanation::* updateFunc)(const InputState& input);


};

