#pragma once
#include "Scene.h"

/// <summary>
/// �p�b�h���p�Q�[���N���A�V�[��
/// </summary>
/// 
class MixGameClearScene : public Scene
{
public:

	MixGameClearScene(SceneManager& manager);
	~MixGameClearScene();

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

	using UpdateFunc_t = void(MixGameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};
