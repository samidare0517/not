#pragma once
#include "Scene.h"

class InputState;

// �^�C�g���V�[��
class TitleScene : public Scene
{
public:

	TitleScene(SceneManager& manager);
	virtual ~TitleScene();

	void Update(const InputState& input);

	void Draw();

private:

	int titleHandle = -1;		// �^�C�g���摜
	int titlerogoHandle = -1;	// �^�C�g�����S�摜

	int starHandle1 = -1;		// ���ꐯ�A�j���[�V�����摜
	int starHandle2 = -1;
	int starHandle3 = -1;
	
	int catHandle1 = -1;		// �L�A�j���[�V�����摜
	int catHandle2 = -1;
	int catHandle3 = -1;
	
	int buttonAhandle = -1;	// �{�^���摜
	int buttonRBhandle = -1;	// RB�{�^���摜
	int buttonLBhandle = -1;	// LB�{�^���摜

	int indexX = 192;		//�摜�T�C�Y�̃C���f�b�N�X
	int indexY = 192;		//�摜�T�C�Y�̃C���f�b�N�X
	int posX = 0;			//���̃A�j���[�V����
	int posY = 0;
	int frameCount = 0;
	int frame = 0;
	
	int starNum = 0;// ���̎�ރ����_���p
	int starRandomNum = 3;// �S�̂̐��o���G�[�V������
	int starX = 0;	// �����`�悳���X
	int starY = 0;	// �����`�悳���Y

	int catNum = 0;	// �L�̎�ރ����_���p
	int catRandomNum = 3;	// �S�̂̔L�o���G�[�V����

	int animationNumber = 17;                        //�A�j���[�V�����i���j
	int imgidx = 2;                                 //�c�̉摜
	int timer = 0;                                  //�A�j���[�V�����̃C���^�[�o��
	int catX = 1500;	// �L�̏����ʒuX
	int catY = 850;	// �L�̏����ʒuY
	
	static constexpr int fadeIntarval = 60;
	int fadeTimer = fadeIntarval;		// �t�F�[�h�^�C�}�[
	int fadeValue = 225;	// ����`�Ƃ̃u�����h�

	int musicTitle = 0;	// �^�C�g��BGM�n���h��
	int seButton = 0;	// ���ɍs���Ƃ���SE�n���h��

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	// �t�F�[�h�A�E�g2����Update�֐�
	void FadeOutUpdate2(const InputState& input);

	// �t�F�[�h�A�E�g3����Update�֐�
	void FadeOutUpdate3(const InputState& input);

	// Update�p�����o�֐��|�C���^
	void (TitleScene::* updateFunc)(const InputState& input);

	// ���A�j���[�V��������Draw�֐�
	void StarAnimation();

	// �L�A�j���[�V��������Draw�֐�
	void CatAnimation();
};

