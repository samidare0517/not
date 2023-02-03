#pragma once
#include "Scene.h"

/// <summary>
/// �Q�[���N���A�V�[��
/// </summary>
class GameClearScene : public Scene
{
private:
	int gameoverH = -1;	// �摜

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;
	using UpdateFunc_t = void(GameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc_ = nullptr;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

public:
	GameClearScene(SceneManager& manager);
	~GameClearScene();

	void Update(const InputState& input);
	void Draw();
};

