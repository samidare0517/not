#include "KeyExplanationScene.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "KeyGameOverScene.h"
#include <time.h>		// �����_���p
#include "DxLib.h"

void TitleScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc = &TitleScene::NormalUpdate;
		fadeValue = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	// ���փ{�^���������ꂽ�玟�̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::next))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &TitleScene::FadeOutUpdate;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyExplanationScene(manager_));
		return;
	}
}

void TitleScene::StarAnimation()
{
	// �����_���ɐ��̃A�j���[�V������`��
	switch (starNum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
						  indexX * posX, indexY * posY,
						  indexX, indexY,
						  1, 0, starHandle1,
						  true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
						  indexX * posX, indexY * posY,
						  indexX, indexY,
						  1, 0, starHandle2,
						  true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
						  indexX * posX, indexY * posY,
						  indexX, indexY,
						  1, 0, starHandle3,
						  true, false);
		break;
	}

	frameCount++;

	if (frameCount > 2)	// 2�t���[�����Ƃɉ摜���E��192�ړ�������
	{
		frameCount = 0;	// �t���[���J�E���g�����Z�b�g
		posX++;	//1���v���X����
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
		starNum = rand() % starRandomNum + 1;		// 1�`3�̗������o��
		starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
		starY = rand() % 650 + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)
	}
}

void TitleScene::CatAnimation()
{
	// �����_���ɔL�̃A�j���[�V������`��
	switch (catNum)
	{
	case 1:
		DrawRectRotaGraph(catX, catY,//�\�����������W�̎w��
			32 * animationNumber,
			32 + (32 * imgidx),		//�؂��荶��(+32�͏�̂悭�킩��Ȃ�����Ȃ��Ă�j
			32, 32,					//���A�����i�摜�̑傫��32�j
			4.0f, 0.0f,				//�g�嗦�A��]�p�x
			catHandle1, true);
		break;

	case 2:
		DrawRectRotaGraph(catX, catY,//�\�����������W�̎w��
			32 * animationNumber,
			32 + (32 * imgidx),		//�؂��荶��(+32�͏�̂悭�킩��Ȃ�����Ȃ��Ă�j
			32, 32,					//���A�����i�摜�̑傫��32�j
			4.0f, 0.0f,				//�g�嗦�A��]�p�x
			catHandle2, true);
		break;

	case 3:
		DrawRectRotaGraph(catX, catY,//�\�����������W�̎w��
			32 * animationNumber,
			32 + (32 * imgidx),		//�؂��荶��(+32�͏�̂悭�킩��Ȃ�����Ȃ��Ă�j
			32, 32,					//���A�����i�摜�̑傫��32�j
			4.0f, 0.0f,				//�g�嗦�A��]�p�x
			catHandle3, true);
		break;
	}

	//�A�j���[�V�������Ō�܂ōs������16�ɖ߂��Ă�����
	if (animationNumber > 19)
	{
		animationNumber = 16;
	}

	timer++;        //���Ԃ̃J�E���g
	
	if (timer >= 16)
	{
		//�C���^�[�o�����傫���Ȃ�����A�j���[�V�����𓮂���
		animationNumber++;
		
		catX -= 30;

		if (0 > catX)	// �L��������o�����ɂȂ�����E����ēx�\������
		{
			// ��ԍŌ�܂ōs������ꏊ�������_���Ő�������@
			srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
			catNum = rand() % catRandomNum + 1;		// 1�`3�̗������o��

			catX = 1632;	// ���R�ɓ���ւ���悤�ɉ�ʊO(x��1632)�̈ʒu����`��
		}
		
		timer = 0;
	}
	
	// �n���h���������_���ɂȂ��Ă��邩���m�F���邽�߂̕\��(�f�o�b�N�p)
//	SetFontSize(30);
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "�L�n���h���ԍ�:%d", catNum);
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
updateFunc(&TitleScene::FadeInUpdate)
{
	// �摜�̃��[�h
	titleHandle = LoadGraph("data/TitleBack.png");
	titlerogoHandle = LoadGraph("data/Titlerogo.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");
	
	catHandle1  = LoadGraph("data/cat/calico_0.png");
	catHandle2  = LoadGraph("data/cat/game_boy_1.png");
	catHandle3  = LoadGraph("data/cat/indigo_0.png");
	
	buttonAhandle = LoadGraph("data/button/buttonA.png");

	//������
	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����

	// ���A�j���[�V�����̂̃����_���֌W�̏���
	starNum = rand() % starRandomNum + 1;		// 1�`3�̗������o��
	starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
	starY = rand() % 650 + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)

	// �L�A�j���[�V�����̃����_���֌W�̏���
	catNum = rand() % catRandomNum + 1;	// 1�`3�̗������o��

	// BGM�̓ǂ݂���
	musicTitle = LoadSoundMem("data/BGM/TitleBGM.mp3");

	// BGM�̉��ʂ𒲐�����
	ChangeVolumeSoundMem(255 * 50 / 100, musicTitle);

	// BGM���Ăяo��
	PlaySoundMem(musicTitle, DX_PLAYTYPE_LOOP, false);

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

TitleScene::~TitleScene()
{
	// �摜�̃f���[�g
	DeleteGraph(titleHandle);
	DeleteGraph(titlerogoHandle);

	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);
	
	DeleteGraph(catHandle1);
	DeleteGraph(catHandle2);
	DeleteGraph(catHandle3);

	DeleteGraph(buttonAhandle);

	// ���y�̃f���[�g
	DeleteSoundMem(musicTitle);
	DeleteSoundMem(seButton);
}

void TitleScene::Update(const InputState& input)
{
	(this ->*updateFunc)(input);
}


void TitleScene::Draw()
{
	// �w�i�`��
	DrawGraph(0, 0, titleHandle, true);

	// �����_���ɂȂ��Ă��邩(�f�o�b�N�p)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "��:% d\n", starnum);
	// �t���[����(�f�o�b�N�p)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "�t���[��:% d\n", frameCount);
	
	StarAnimation();	// ���̃A�j���[�V�������Ăяo��
	CatAnimation();		// �L�̃A�j���[�V�������Ăяo��

	DrawGraph(200, 340, titlerogoHandle, true);	// �^�C�g�����S��`��

	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	// UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g

	// �_�ŏ���
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		DrawGraph(790, 610, buttonAhandle, true);
		SetFontSize(50);
		DrawFormatString(660, 650, GetColor(255, 255, 77), "PUSH");
	}

	// �V�[���m�F�p
//	SetFontSize(50);
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�g��");

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	
	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
