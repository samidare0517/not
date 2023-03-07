#include "PauseScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


PauseScene::PauseScene(SceneManager& manager) : Scene(manager)
{
	// �摜�̃��[�h
	Handle = LoadGraph("data/cat/black_1.png");
	buttonSTARThandle = LoadGraph("data/button/buttonSTART.png");
}

PauseScene::~PauseScene()
{
	// �摜�̃f���[�g
	DeleteGraph(Handle);
	DeleteGraph(buttonSTARThandle);
}

void PauseScene::Update(const InputState& input)
{
	if (input.IsTriggred(InputType::pause))
	{
		// �|�[�Y�V�[���ւ̈ڍs�p��SE�̓ǂݍ���
		seButtonPause = LoadSoundMem("data/BGM/PauseSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 150 / 100, seButtonPause);

		// SE���Ăяo��
		PlaySoundMem(seButtonPause, DX_PLAYTYPE_BACK, false);

		manager_.PopScene();
		return;
	}
}

void PauseScene::Draw()
{
	constexpr int pw_width  = 500;	// �|�[�Y�g�̕�
	constexpr int pw_height = 500;	// �|�[�Y�g�̍���
	constexpr int pw_start_x = (1600 - pw_width) / 2;	// �|�[�Y�g��
	constexpr int pw_start_y = (900 - pw_height) / 2;	// �|�[�Y�g��

//	SetDrawBlendMode(DX_BLENDMODE_MULA, 128);	// ��Z����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	// ��ʂ��Â�����
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);

	// �ʏ�`��ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �̃|�[�Y�E�C���h�E
	DrawBox(pw_start_x, pw_start_y,
			pw_start_x + pw_width,
			pw_start_y + pw_height,
			GetColor(71, 83 ,162), true);

	// �|�[�Y�E�B���h�E�g��
	DrawBox(pw_start_x, pw_start_y,
			pw_start_x + pw_width,
			pw_start_y + pw_height,
			0xffffff, false);

	// �|�[�Y�����b�Z�[�W
	SetFontSize(80);
	DrawString(pw_start_x + 20, pw_start_y + 210, "Pauseing...", GetColor(255, 255, 127));

	// �߂�ē�
	DrawGraph(630, 645, buttonSTARThandle, true);
	SetFontSize(20);
	DrawFormatString(560, 670, GetColor(255, 255, 255), "�߂� �E�E�E");

	//�A�j���[�V�������Ō�܂ōs������[���ɖ߂��Ă�����
	if (animationNumber > 14)
	{
		animationNumber = 0;
	}

	timer++;        //���Ԃ̃J�E���g
	if (timer >= 15)
	{
		//�C���^�[�o�����傫���Ȃ�����A�j���[�V�����𓮂���
		animationNumber++;
		timer = 0;
	}

	DrawRectRotaGraph(1000, 670,			//�\�����������W�̎w��
		32 * animationNumber, 32 + (32 * imgidx),			//�؂��荶��    �i+32�͏�̂悭�킩��Ȃ�����Ȃ��Ă�j
		32, 32,							//���A�����i�摜�̑傫��32�j
		2.5f, 0.0f,						//�g�嗦�A��]�p�x
		Handle, true);

}
