#include "GameExplanation.h"
#include "KeyExplanationScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "KeyGameoverScene.h"
#include <time.h>		// �����_���p
#include "DxLib.h"

void GameExplanation::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc = &GameExplanation::NormalUpdate;
		fadeValue = 0;
	}
}

void GameExplanation::NormalUpdate(const InputState& input)
{
	// ���փ{�^���������ꂽ�玟�̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::button))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &GameExplanation::FadeOutUpdate;
	}
}

void GameExplanation::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyExplanationScene(manager_));
		return;
	}
}



GameExplanation::GameExplanation(SceneManager& manager) : Scene(manager),
updateFunc(&GameExplanation::FadeInUpdate)
{
	// �摜�̃��[�h
	explanationHandle = LoadGraph("data/KeyGameSetumei.png");
	buttonRBhandle = LoadGraph("data/button/buttonRB.png");

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

GameExplanation::~GameExplanation()
{
	// �摜�̃f���[�g
	DeleteGraph(explanationHandle);
	DeleteGraph(buttonRBhandle);

	// ���y�̃f���[�g
	DeleteSoundMem(seButton);
}

void GameExplanation::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}


void GameExplanation::Draw()
{
	// �w�i�`��
	DrawGraph(0, 0, explanationHandle, true);
	DrawGraph(20, 0, buttonRBhandle, true);

	// �e�X�g�p���W�Œ�A�j���[�V����
	//DrawRectRotaGraph(200, 200,
	//	left, top, rigth, bottom,
	//	1, 0, starHandle1, true, false);

	// �����_���ɂȂ��Ă��邩(�f�o�b�N�p)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "��:% d\n", starnum);
	// �t���[����(�f�o�b�N�p)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "�t���[��:% d\n", frameCount);

	
	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	// UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g

	SetFontSize(100);
	DrawFormatString(550, 200,GetColor(255, 255, 255), "�Q�[������");
	SetFontSize(50);
	DrawFormatString(450, 450, GetColor(255, 255, 255),
		"�����ɕ\�������w���ɏ]����");
	DrawFormatString(400, 550, GetColor(255, 255, 255),
		"�������Q�[���p�b�g�𑀍삵�Ă�������");


	
	SetFontSize(30);
	DrawFormatString(100, 28, GetColor(255, 255, 77),
		"�߂�");
	



	//	DrawCircle(60, 60, 10, GetColor(255, 255, 255), true);


		// �V�[���m�F�p
	//	SetFontSize(50);
	//	DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�g��");

		// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}