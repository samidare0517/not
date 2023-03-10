#pragma once
#include "Scene.h"
#include <memory>

/// <summary>
/// �p�b�h���p����
/// </summary>
 
class PadExplanationScene : public Scene
{
public:

	PadExplanationScene(SceneManager& manager);
	virtual ~PadExplanationScene();

	void Update(const InputState& input);
	void Draw();

private:

	int Handle = -1;		// �^�C�g���摜
	int buttonAhandle = -1;	// A�{�^���摜
	int buttonBhandle = -1;	// B�{�^���摜
	int buttonXhandle = -1;	// X�{�^���摜
	int buttonYhandle = -1;	// Y�{�^���摜

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
	void (PadExplanationScene::* updateFunc_)(const InputState& input);

	void Function();

};

