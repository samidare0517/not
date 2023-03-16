#pragma once
#include "Scene.h"

/// <summary>
/// �p�b�h���p�Q�[���N���A�V�[��
/// </summary>

class PadGameClearScene : public Scene
{
public:

	PadGameClearScene(SceneManager& manager);
	virtual ~PadGameClearScene();

	void Update(const InputState& input);
	void HanabiAnimation();
	void Draw();

private:

	int gameclearHandle = -1;	// �摜
	int buttonBACKhandle = -1;	// BACK�{�^���摜
	int buttonAhandle = -1;		// A�{�^���摜
	int buttonBhandle = -1;		// B�{�^���摜
	
	int starHandle1 = -1;		// ���ꐯ�A�j���[�V�����摜
	int starHandle2 = -1;
	int starHandle3 = -1;

	int hanabiHandle1 = -1;		// �ԉ΃A�j���[�V����
	int hanabiHandle2 = -1;
	int hanabiHandle3 = -1;
	int hanabiHandle4 = -1;
	int hanabiHandle5 = -1;
	int hanabiHandle6 = -1;

	int starIndexX = 192;		//�摜�T�C�Y�̃C���f�b�N�X
	int starIndexY = 192;		//�摜�T�C�Y�̃C���f�b�N�X
	
	int starPosX = 0;			//���̃A�j���[�V����
	int starPosY = 0;
	
	int frameCount = 0;
	int frame = 0;

	int starNum = 0;// ���̎�ރ����_���p
	int randomNum = 3;// �S�̖̂��o���G�[�V������
	
	int starX = 0;	// �����`�悳���X
	int starY = 0;	// �����`�悳���Y

	int hanabiAnimationNumber = 0;
	int hanabiImgIdx = 0;
	int timer = 0;

	int hanabiNum = 0;	// �ԉ΂̎�ރ����_���p
	int hanabiRandomNum = 3;	// �ԉ΂̃p�^�[���̐�

	int musicClear = 0;	// �N���ABGM�n���h��
	int seButton = 0;	// ���ɍs���Ƃ���SE�n���h��
	int seBackButton = 0;	// �^�C�g���֖߂�Ƃ���SE�n���h��
	int seHanabi = 0;	// �ԉ�SE

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
	void StarAnimation();

	using UpdateFunc_t = void(PadGameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};

