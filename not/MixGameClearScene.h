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
	int starHandle1 = -1;		// ���ꐯ�A�j���[�V�����摜
	int starHandle2 = -1;
	int starHandle3 = -1;

	int left = 0;
	int top = 0;
	int rigth = 192;
	int bottom = 192;
	int frameCount = 0;
	float changeY = false;
	int frame = 0;

	int starnum = 0;// ���̎�ރ����_���p
	int randomnum = 3;// �S�̖̂��o���G�[�V������
	int starX = 0;	// �����`�悳���X
	int starY = 0;	// �����`�悳���Y

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

