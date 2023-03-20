#pragma once
#include "Scene.h"

/// <summary>
/// �Q�[���Z���N�g���
/// </summary>

class GameSelect : public Scene
{
public:

	GameSelect(SceneManager& manager);
	virtual ~GameSelect();

	void Update(const InputState& input);
	void Draw();

private:

	int backScreenHandle = -1;
	int buttonAhandle = -1;	// A�{�^���摜
	int buttonBhandle = -1;	// B�{�^���摜
	int buttonXhandle = -1;	// X�{�^���摜
	int buttonRBHandle = -1;	// RB�{�^���摜

	int seButton = 0;	// ���ɍs���Ƃ���SE�n���h��

	static constexpr int fadeInterval = 60;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(const InputState& input);

	// �ʏ펞��Update�֐�
	void NormalUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate2(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate3(const InputState& input);

	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate4(const InputState& input);


	// Update�p�����o�֐��|�C���^
	void (GameSelect::* updateFunc)(const InputState& input);

};

