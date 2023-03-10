#pragma once
#include "Scene.h"

/// <summary>
/// �p�b�h���p�Q�[���I�[�o�[�V�[��
/// </summary>

class PadGameoverScene : public Scene
{
public:

	PadGameoverScene(SceneManager& manager);
	virtual ~PadGameoverScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameoverHandle = -1;	// �摜
	int buttonBACKhandle = -1;	// BACK�{�^���摜
	int buttonBhandle = -1;		// B�{�^���摜
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

	int musicOver = 0;	// �Q�[���I�[�o�[BGM�n���h��
	int seButton = 0;	// ���ɍs���Ƃ���SE�n���h��
	int seBackButton = 0;	// �^�C�g���֖߂�Ƃ���SE�n���h��

	static constexpr int fadeInterval = 120;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	// �A�j���[�V��������Draw�֐�
	void DrawAnimation();

	using UpdateFunc_t = void(PadGameoverScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;
};

