#include "MixGameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MixField.h"
#include "Pad.h"
#include <time.h>		// �����_���p
#include "DxLib.h"

void MixGameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &MixGameoverScene::NormalUpdate;
		fadeValue = 0;
	}
}

void MixGameoverScene::NormalUpdate(const InputState& input)
{
	// �^�C�g���̏ꍇ
	if (input.IsTriggred(InputType::title))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seBackButton);

		// SE���Ăяo��
		PlaySoundMem(seBackButton, DX_PLAYTYPE_BACK, false);

		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
	// ���X�^�[�g�̏ꍇ
	if (input.IsTriggred(InputType::prev))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		manager_.CangeScene(new MixField(manager_));
		return;
	}
}

void MixGameoverScene::FadeOutUpdate(const InputState& input)
{

}

void MixGameoverScene::DrawAnimation()
{
	// �����_���ɃA�j���[�V������`��
	switch (starnum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
			indexX * posX, indexY * posY, indexX, indexY,
			1, 0, starHandle1, true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
			indexX * posX, indexY * posY, indexX, indexY,
			1, 0, starHandle2, true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
			indexX * posX, indexY * posY, indexX, indexY,
			1, 0, starHandle3, true, false);
		break;
	}

	frameCount++;

	if (frameCount > 2)	// 2�t���[�����Ƃɉ摜���E��192�ړ�������
	{
		frameCount = 0;	// �t���[���J�E���g�����Z�b�g
		posX++;	// 1���v���X����
	}
	if (posX >= 5)	// �摜�̉E�܂ňړ�����ƍ��ɖ߂�
	{
		posX = 0;	// 0�ɖ߂�
		posY += 1;	// �A�j���[�V��������i������

	}
	if (posY >= 4)	// ��ԍŌ�̒i���傫���Ȃ낤�Ƃ�����
	{
		posY = 0;	// �[���ɖ߂�

		// ��ԍŌ�܂ōs������ꏊ�������_���Ő�������
		srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
		starnum = rand() % randomnum + 1;		// 1�`3�̗������o��
		starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
		starY = rand() % 650 + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)
	}
}

MixGameoverScene::MixGameoverScene(SceneManager& manager) : Scene(manager),
updateFunc(&MixGameoverScene::FadeInUpdate)
{
	// �摜�̃��[�h
	gameoverHandle = LoadGraph("data/OverBack.png");
	buttonBACKhandle = LoadGraph("data/button/buttonBACK.png");
	buttonBhandle = LoadGraph("data/button/buttonB.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");

	//������
	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
	starnum = rand() % randomnum + 1;		// 1�`3�̗������o��
	starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
	starY = rand() % 650 + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)

	// BGM�̓ǂ݂���
	musicOver = LoadSoundMem("data/BGM/GameOverBGM.mp3");

	// BGM�̉��ʂ𒲐�����
	ChangeVolumeSoundMem(255 * 50 / 100, musicOver);

	// BGM���Ăяo��
	PlaySoundMem(musicOver, DX_PLAYTYPE_LOOP, false);

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");

	// SE�̓ǂݍ���
	seBackButton = LoadSoundMem("data/BGM/BackTitleSE.mp3");

}

MixGameoverScene::~MixGameoverScene()
{
	// �摜�̃f���[�g
	DeleteGraph(gameoverHandle);
	DeleteGraph(buttonBACKhandle);
	DeleteGraph(buttonBhandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);

	// ���y�̃f���[�g
	DeleteSoundMem(musicOver);
	DeleteSoundMem(seButton);
	DeleteSoundMem(seBackButton);
}

void MixGameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void MixGameoverScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, gameoverHandle, true);
	
	// �����_���ɂȂ��Ă��邩(�f�o�b�N�p)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "��:% d\n", starnum);
	// �t���[����(�f�o�b�N�p)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "�t���[��:% d\n", frameCount);

	DrawAnimation();	// �A�j���[�V�������Ăяo��

	// �\���p����
	ChangeFont("Comic Sans MS");	// Comic Sans MS�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g
	SetFontSize(150);
	DrawFormatString(260, 300, GetColor(191, 127, 255), "GAME OVER...");


	DrawGraph(900, 550, buttonBACKhandle, true);
	DrawGraph(900, 660, buttonBhandle, true);


	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	//UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g
	SetFontSize(50);

	DrawFormatString(540, 600, GetColor(127, 255, 255), "TITLE");
	DrawFormatString(500, 700, GetColor(255, 127, 127), "RESTART");
	DrawFormatString(800, 600, GetColor(255, 255, 255), "�E�E�E");
	DrawFormatString(800, 700, GetColor(255, 255, 255), "�E�E�E");


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

