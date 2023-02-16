#pragma once
#include "Scene.h"

/// <summary>
/// �p�b�h���p�Q�[���I�[�o�[�V�[��
/// </summary>

class PadGameoverScene : public Scene
{
public:

	PadGameoverScene(SceneManager& manager);
	~PadGameoverScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameoverHandle = -1;	// �摜

	static constexpr int fadeInterval = 120;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(PadGameoverScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;
};

