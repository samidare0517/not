#pragma once
#include "Scene.h"

/// <summary>
/// �L�[���p�Q�[���I�[�o�[�V�[��
/// </summary>
class KeyGameoverScene : public Scene
{
public:

	KeyGameoverScene(SceneManager& manager);
	~KeyGameoverScene();

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

	using UpdateFunc_t = void(KeyGameoverScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};

