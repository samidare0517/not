#pragma once
#include "Scene.h"
#include <memory>

class KeyExplanationScene : public Scene
{

public:

	KeyExplanationScene(SceneManager& manager);
	~KeyExplanationScene();

	void Update(const InputState& input);
	void Draw();

private:

	static constexpr int fadeIntarval = 60;
	int titleHandle = -1;		// �^�C�g���摜
	int fadeTimer = fadeIntarval;		// �t�F�[�h�^�C�}�[
	int fadeValue = 225;	// ����`�Ƃ̃u�����h�

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	// Update�p�����o�֐��|�C���^
	void (KeyExplanationScene::* updateFunc_)(const InputState& input);

	void Function();

};


