#pragma once
#include "Scene.h"

/// <summary>
/// �Q�[���N���A�V�[��
/// </summary>
class GameClearScene : public Scene
{
public:

	GameClearScene(SceneManager& manager);
	~GameClearScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameclearH = -1;	// �摜

	static constexpr int fade_interval = 120;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void(GameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc_ = nullptr;

};

