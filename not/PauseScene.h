#pragma once
#include "Scene.h"

class InputState;
class SceneManager;

/// <summary>
/// �|�[�Y�V�[��
/// </summary>

class PauseScene : public Scene
{
public:
	PauseScene(SceneManager& manager);
	~PauseScene();

	virtual void Update(const InputState& input) override;
	void Draw();

private:
	int Handle = -1;		// �A�j���[�V�����摜
	int buttonSTARThandle = -1;	// �߂�ē��p�摜
	int animationNumber = 0;                        //�A�j���[�V�����i���j
	int imgidx = 2;                                 //�c�̉摜
	int timer = 0;                                  //�A�j���[�V�����̃C���^�[�o��

	int seButtonPause = 0;	// �|�[�Y�V�[������ڍs����Ƃ���SE�n���h��
};

