#pragma once
#include "Scene.h"

/// <summary>
/// �p�b�h���p�Q�[���N���A�V�[��
/// </summary>

class MixGameClearScene : public Scene
{
public:

	MixGameClearScene(SceneManager& manager);
	~MixGameClearScene();

	void Update(const InputState& input);
	void Draw();

private:

	int gameclearHandle = -1;	// �摜
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

	int musicClear = 0;	// �N���ABGM�n���h��
	int seButton = 0;	// ���ɍs���Ƃ���SE�n���h��
	int seBackButton = 0;	// �^�C�g���֖߂�Ƃ���SE�n���h��

	static constexpr int fadeInterval = 60;
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

	using UpdateFunc_t = void(MixGameClearScene::*)(const InputState&);
	UpdateFunc_t updateFunc = nullptr;

};

