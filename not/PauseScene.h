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
	virtual ~PauseScene();

	virtual void Update(const InputState& input) override;
	void CatInit();
	void CatAnimationDraw();
	void Draw();

private:
	
	int catHandle1 = -1;		// �L�A�j���[�V�����摜
	int catHandle2 = -1;
	int catHandle3 = -1;

	int catNum = 0;	// �L�̎�ރ����_���p
	int catRandomNum = 3;	// �S�̂̔L�o���G�[�V����

	int animationNumber = 0;                        //�A�j���[�V�����i���j
	int imgidx = 2;                                 //�c�̉摜
	int timer = 0;                                  //�A�j���[�V�����̃C���^�[�o��

	int buttonSTARThandle = -1;	// �߂�ē��p�摜

	int seButtonPause = 0;	// �|�[�Y�V�[������ڍs����Ƃ���SE�n���h��
};

