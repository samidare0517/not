#include "PauseScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


PauseScene::PauseScene(SceneManager& manager) : Scene(manager)
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(const InputState& input)
{
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PopScene();
		return;
	}
}

void PauseScene::Draw()
{
	constexpr int pw_width = 500;	// �|�[�Y�g�̕�
	constexpr int pw_height = 500;	// �|�[�Y�g�̍���
	constexpr int pw_start_x = (1600 - pw_width) / 2;	// �|�[�Y�g��
	constexpr int pw_start_y = (900 - pw_height) / 2;	// �|�[�Y�g��

//	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);	// ��Z����

	// �|�[�Y�E�B���h�E�Z���t�@��(��)
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width,
		pw_start_y + pw_height,
		GetColor(188, 221, 255), true);

	// �ʏ�`��ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �|�[�Y�E�B���h�E�g��
	DrawBox(pw_start_x, pw_start_y,
		pw_start_x + pw_width,
		pw_start_y + pw_height,
		0xffffff, false);

	// �|�[�Y�����b�Z�[�W
	SetFontSize(50);
	DrawString(pw_start_x + 10, pw_start_y + 10, "Pauseing", GetColor(255, 255, 127));
}
