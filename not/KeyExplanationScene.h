#pragma once
#include "Scene.h"
#include <memory>

/// <summary>
/// �L�[�̖�����
/// </summary>

class KeyExplanationScene : public Scene
{

public:

	KeyExplanationScene(SceneManager& manager);
	virtual ~KeyExplanationScene();

	void Update(const InputState& input);
	void Draw();

private:

	int Handle = -1;		// �摜
	int buttonAhandle = -1;	// A�{�^���摜
	int buttonRBhandle = -1;	// RB�{�^���摜
	int buttonPadhandle = -1;	// �\���{�^���摜
	int buttonLShandle = -1;	// LS�X�e�B�b�N�摜

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

	// �t�F�[�h�A�E�g2����Update�֐�
	void FadeOutUpdate2(const InputState& input);

	// Update�p�����o�֐��|�C���^
	void (KeyExplanationScene::* updateFunc_)(const InputState& input);

	void Function();

};


