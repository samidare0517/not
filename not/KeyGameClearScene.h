#pragma once
#include "Scene.h"

/// <summary>
/// �L�[���p�Q�[���N���A�V�[��
/// </summary>
/// 
class KeyGameClearScene : public Scene
{
public:

	KeyGameClearScene(SceneManager& manager);
	~KeyGameClearScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameclearHandle = -1;	// �摜

	static constexpr int fadeInterval = 120;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(KeyGameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};

