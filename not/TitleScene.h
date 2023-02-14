#pragma once
#include "Scene.h"

class InputState;

// �^�C�g���V�[��
class TitleScene : public Scene
{
public:

	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);
	void Draw();

private:

	int titleHandle = -1;		// �^�C�g���摜

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
	void (TitleScene::* updateFunc)(const InputState& input);

	void Function();

};

