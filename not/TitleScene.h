#pragma once
#include "Scene.h"

class InputState;

// �^�C�g���V�[��
class TitleScene : public Scene
{
public:

	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);

	void Draw();

private:

	int titleHandle = -1;		// �^�C�g���摜
	int starHandle1 = -1;		// ���ꐯ�A�j���[�V�����摜
	int starHandle2 = -1;
	int starHandle3 = -1;
	

	int indexX = 192;		//�摜�T�C�Y�̃C���f�b�N�X
	int indexY = 192;		//�摜�T�C�Y�̃C���f�b�N�X
	int posX = 0;			//���̃A�j���[�V����
	int posY = 0;
	int frameCount = 0;
	int frame = 0;
	
	int starnum = 0;// ���̎�ރ����_���p
	int randomnum = 3;// �S�̖̂��o���G�[�V������
	int starX = 0;	// �����`�悳���X
	int starY = 0;	// �����`�悳���Y

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

	// Update�p�����o�֐��|�C���^
	void (TitleScene::* updateFunc)(const InputState& input);

	// �A�j���[�V��������Draw�֐�
	void DrawAnimation();
};

