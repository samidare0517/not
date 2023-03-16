#include "KeyGameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "KeyField.h"
#include "PadExplanationScene.h"
#include <time.h>		// �����_���p
#include "DxLib.h"

void KeyGameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &KeyGameClearScene::NormalUpdate;
		fadeValue = 0;
	}
}

void KeyGameClearScene::NormalUpdate(const InputState& input)
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

	// ���̖��ɐi�ޏꍇ
	if (input.IsTriggred(InputType::next))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &KeyGameClearScene::FadeOutUpdate;
	}

	// ���X�^�[�g�̏ꍇ
	if (input.IsTriggred(InputType::prev))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void KeyGameClearScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval));
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new PadExplanationScene(manager_));
		return;
	}
}

void KeyGameClearScene::StarAnimation()
{
	// �����_���ɃA�j���[�V������`��
	switch (starNum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
						  starIndexX * starPosX, starIndexY * starPosY,
						  starIndexX, starIndexY,
						  1, 0, starHandle1,
						  true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
						  starIndexX * starPosX, starIndexY * starPosY,
						  starIndexX, starIndexY,
						  1, 0, starHandle2,
						  true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
						  starIndexX * starPosX, starIndexY * starPosY,
						  starIndexX, starIndexY,
						  1, 0, starHandle3,
						  true, false);
		break;
	}

	frameCount++;

	if (frameCount > 2)	//2�t���[�����Ƃɉ摜���E��192�ړ�������
	{
		frameCount = 0;	// �t���[���J�E���g�����Z�b�g
		starPosX++;	//1���v���X����
	}
	if (starPosX >= 5)	// �摜�̉E�܂ňړ�����ƍ��ɖ߂�
	{
		starPosX = 0;	//0�ɖ߂�
		starPosY += 1;	// �A�j���[�V��������i������

	}
	if (starPosY >= 4)	//��ԍŌ�̒i���傫���Ȃ낤�Ƃ�����
	{
		starPosY = 0;	//�[���ɖ߂�

		//��ԍŌ�܂ōs������ꏊ�������_���Ő�������
		srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
		starNum = rand() % randomNum + 1;		// 1�`3�̗������o��
		starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
		starY = rand() % 650 + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)
	}
}

void KeyGameClearScene::HanabiAnimation()
{
	// �����_����3�p�^�[���̉ԉ΂�\������
	switch (hanabiNum)
	{
	case 1:
		DrawRectRotaGraph(150, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle1, true);

		DrawRectRotaGraph(1400, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle2, true);

		break;

	case 2:
		DrawRectRotaGraph(150, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle3, true);

		DrawRectRotaGraph(1400, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle5, true);

		break;

	case 3:
		DrawRectRotaGraph(150, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle4, true);

		DrawRectRotaGraph(1400, 370,
			120 * (hanabiAnimationNumber), hanabiImgIdx,
			120, 120,
			1.2f, 0.0f,
			hanabiHandle6, true);

		break;
	}

	//�A�j���[�V�������Ō�܂ōs������14�ɖ߂��Ă�����
	if (hanabiAnimationNumber > 14)
	{
		hanabiAnimationNumber = 0;

		// SE�̓ǂݍ���
		seHanabi = LoadSoundMem("data/BGM/HanabiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 100 / 100, seHanabi);

		// SE���Ăяo��
		PlaySoundMem(seHanabi, DX_PLAYTYPE_BACK, false);

		srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
		hanabiNum = rand() % hanabiRandomNum + 1;		// 1�`3�̗������o��		
	}

	timer++;        //���Ԃ̃J�E���g

	if (timer >= 5)
	{
		//�C���^�[�o�����傫���Ȃ�����A�j���[�V�����𓮂���
		hanabiAnimationNumber++;

		timer = 0;
	}

	

	// �f�o�b�N�p
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "�����ڂ� %d", hanabiNum);
}

KeyGameClearScene::KeyGameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&KeyGameClearScene::FadeInUpdate)
{
	// �摜�̃��[�h
	gameClearHandle = LoadGraph("data/ClearBack.png");
	buttonBACKhandle = LoadGraph("data/button/buttonBACK.png");
	buttonAhandle = LoadGraph("data/button/buttonA.png");
	buttonBhandle = LoadGraph("data/button/buttonB.png");

	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");

	hanabiHandle1 = LoadGraph("data/png/hanabi1.png");
	hanabiHandle2 = LoadGraph("data/png/hanabi2.png");
	hanabiHandle3 = LoadGraph("data/png/hanabi3.png");
	hanabiHandle4 = LoadGraph("data/png/hanabi4.png");
	hanabiHandle5 = LoadGraph("data/png/hanabi5.png");
	hanabiHandle6 = LoadGraph("data/png/hanabi6.png");

	//������
	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
	starNum = rand() % randomNum + 1;		// 1�`3�̗������o��
	starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
	starY = rand() % 650 + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)

	hanabiNum = rand() % hanabiRandomNum + 1;	// 1�`3�̗������o��

	// BGM�̓ǂ݂���
	musicClear = LoadSoundMem("data/BGM/GameClearBGM.mp3");

	// BGM�̉��ʂ𒲐�����
	ChangeVolumeSoundMem(255 * 50 / 100, musicClear);

	// BGM���Ăяo��
	PlaySoundMem(musicClear, DX_PLAYTYPE_LOOP, false);

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");

	// SE�̓ǂݍ���
	seBackButton = LoadSoundMem("data/BGM/BackTitleSE.mp3");

}

KeyGameClearScene::~KeyGameClearScene()
{
	// �摜�̃f���[�g
	DeleteGraph(gameClearHandle);
	DeleteGraph(buttonBACKhandle);
	DeleteGraph(buttonAhandle);
	DeleteGraph(buttonBhandle);

	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);

	DeleteGraph(hanabiHandle1);
	DeleteGraph(hanabiHandle2);
	DeleteGraph(hanabiHandle3);
	DeleteGraph(hanabiHandle4);
	DeleteGraph(hanabiHandle5);
	DeleteGraph(hanabiHandle6);


	// ���y�̃f���[�g
	DeleteSoundMem(musicClear);
	DeleteSoundMem(seButton);
	DeleteSoundMem(seBackButton);
	DeleteSoundMem(seHanabi);
}

void KeyGameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void KeyGameClearScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, gameClearHandle, true);


	// �����_���ɂȂ��Ă��邩(�f�o�b�N�p)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "��:% d\n", starnum);
	// �t���[����(�f�o�b�N�p)
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "�t���[��:% d\n", frameCount);
	
	// �ԉ΂�`��
	HanabiAnimation();

	// ����`��
	StarAnimation();

	// �\���p����

	ChangeFont("Lucida Bright");	//UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g
	
	SetFontSize(150);
	DrawFormatString(250, 300, GetColor(255, 255, 133), "GAME CLEAR");


	DrawGraph(900, 550, buttonBACKhandle, true);
	DrawGraph(900, 660, buttonAhandle, true);
	DrawGraph(900, 760, buttonBhandle, true);


	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	//UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g
	SetFontSize(50);

	DrawFormatString(540, 600, GetColor(127, 255, 255), "TITLE");
	DrawFormatString(550, 700, GetColor(127, 255, 127), "NEXT");
	DrawFormatString(500, 800, GetColor(255, 127, 127), "RESTART");
	DrawFormatString(800, 600, GetColor(255, 255, 255), "�E�E�E");
	DrawFormatString(800, 700, GetColor(255, 255, 255), "�E�E�E");
	DrawFormatString(800, 800, GetColor(255, 255, 255), "�E�E�E");


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}