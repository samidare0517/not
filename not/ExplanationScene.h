#pragma once
#include "Scene.h"
#include <memory>

class ExplanationScene : public Scene
{
private:

	static constexpr int fade_intarval = 60;
	int titleH_ = -1;		// �^�C�g���摜
	int fadeTimer_ = fade_intarval;		// �t�F�[�h�^�C�}�[
	int fadeValue_ = 225;	// ����`�Ƃ̃u�����h�

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	// Update�p�����o�֐��|�C���^
	void (ExplanationScene::* updateFunc_)(const InputState& input);

	void Function();


public:

	ExplanationScene(SceneManager& manager);
	~ExplanationScene();

	void Update(const InputState& input);
	void Draw();

};


