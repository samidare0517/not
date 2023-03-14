#include "PadField.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PadGameoverScene.h"
#include "PadGameClearScene.h"
#include "PauseScene.h"
#include "DxLib.h"
#include "Pad.h"
#include <time.h>		// �����_���p
#include"TimeBar.h"

namespace
{
	bool answerCheck = false;
	TimeBar kTime;
}

void PadField::FadeInUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &PadField::NormalUpdate;
	}
}

PadField::PadField(SceneManager& manager) :Scene(manager),
updateFunc(&PadField::FadeInUpdate)
{
	Init();
}

PadField::~PadField()
{
	// �摜�̃f���[�g
	DeleteGraph(handle);
	DeleteGraph(maruHandle);
	DeleteGraph(batuHandle);
	DeleteGraph(buttonSTARThandle);

	// ���y�̃f���[�g
	DeleteSoundMem(musicGameScene);
	DeleteSoundMem(seButtonYes);
	DeleteSoundMem(seButtonNo);
	DeleteSoundMem(seButtonPause);
}

void PadField::Init()
{
	handle = LoadGraph("data/Back.png");	// �^�C���o�[�p�摜

	maruHandle = LoadGraph("data/maru.png");	// ����p�}���摜

	batuHandle = LoadGraph("data/batu.png");	// ����p�o�c�摜

	buttonSTARThandle = LoadGraph("data/button/buttonSTART.png");	// �|�[�Y�{�^���p�摜

	// BGM�̓ǂ݂���
	musicGameScene = LoadSoundMem("data/BGM/GameSceneBGM.mp3");

	// BGM�̉��ʂ𒲐�����
	ChangeVolumeSoundMem(255 * 30 / 100, musicGameScene);

	// BGM���Ăяo��
	PlaySoundMem(musicGameScene, DX_PLAYTYPE_LOOP, false);

	kTime.Init();

	answerNum = 0;	// ���̐��𐔃J�E���g��0�ɂ���(������)

	question = 30;	// �c���萔��������

	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
	num = rand() % randomnum + 1;		// 1�`8�̗������o��
}

void PadField::NormalUpdate(const InputState& input)
{
	Pad::Update();
	if (countDown == 0)	// �J�E���g�_�E����0�ɂȂ�����kTime.Update���Ăяo��
	{
		kTime.Update();
	}
	CountDownUpdate();

	if (answerCheck == true)	// �����������ꂽ�玟�̖���
	{
		for (int i = 0; i < questionNum; i++)		// 30��J��Ԃ�
		{
			num = rand() % randomnum + 1;
		}
		answerNum++;
		question--;
	}
	else if (kTime.Check() == true)	// �^�C���o�[��0�ɂȂ��Ă�����Q�[���I�[�o�[������
	{
		TimeUp();
	}

	// ���𐔂�30�ɂȂ�����N���A��ʂ�
	SetFontSize(50);
	if (answerNum == 30)
	{
		answerCheck = false;	// �����̃t���O�̏�����

		// �w��̉񐔐���������Q�[���N���A�V�[���ɍs��
		manager_.CangeScene(new PadGameClearScene(manager_));
		return;
	}
	// �f�o�b�N�p
//	DrawFormatString(0, 400, GetColor(255, 255, 255), "��萔:%d", answerNum);

	answerCheck = false;	// �����̃t���O�̏�����

	// �����_���ɂȂ��Ă��邩���ׂ�(�f�o�b�N�p)
//	DrawFormatString(0, 200, GetColor(255, 255, 255), "���:% d", num);

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (countDown == 0)	// �J�E���g��0�ɂȂ�������͂��󂯕t����
	{
		// ***�ʏ���***
		// Y������
		if (num == 1)
		{
			if (Pad::isTrigger(PAD_INPUT_4))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				MissPressY();			// �듚�������Ăяo��
			}
		}

		// A������
		if (num == 2)
		{
			if (Pad::isTrigger(PAD_INPUT_1))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				MissPressA();		// �듚�������Ăяo��
			}
		}

		// X������
		if (num == 3)
		{
			if (Pad::isTrigger(PAD_INPUT_3))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				MissPressX();		// �듚�������Ăяo��
			}
		}

		// B������
		if (num == 4)
		{
			if (Pad::isTrigger(PAD_INPUT_2))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				MissPressB();		// �듚�������Ăяo��
			}
		}

		// ***����Ȃ����***

		// Y����Ȃ��@(ABX����)
		if (num == 5)
		{
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
				Pad::isTrigger(PAD_INPUT_3))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				NotPressY();		// �듚�������Ăяo��
			}
		}

		//A����Ȃ��@(BXY����)
		if (num == 6)
		{
			if (Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
				Pad::isTrigger(PAD_INPUT_4))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				NotPressA();		// �듚�������Ăяo��
			}
		}

		// X����Ȃ��@(ABY����)
		if (num == 7)
		{
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
				Pad::isTrigger(PAD_INPUT_4))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				NotPressX();		// �듚�������Ăяo��
			}
		}

		// B����Ȃ��@(AXY����)
		if (num == 8)
		{
			if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_3) ||
				Pad::isTrigger(PAD_INPUT_4))
			{
				answerCheck = true;		// �����������ꂽ��}��
			}
			else
			{
				NotPressB();		// �듚�������Ăяo��
			}
		}
	}

	// P�L�[�Ń|�[�Y�V�[��
	if (input.IsTriggred(InputType::pause))
	{
		// �|�[�Y�V�[���ւ̈ڍs�p��SE�̓ǂݍ���
		seButtonPause = LoadSoundMem("data/BGM/PauseSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 150 / 100, seButtonPause);

		// SE���Ăяo��
		PlaySoundMem(seButtonPause, DX_PLAYTYPE_BACK, false);
		manager_.PushScene(new PauseScene(manager_));
	}
}

void PadField::CountDownUpdate()
{
	if (fadeTimer == 0)
	{
		countDown--;	// �t�F�[�h�^�C�}�[��0�ɂȂ�����(�t�F�[�h���I��莟��)�J�E���g�_�E��������
	}
	if (countDown < 0)
	{
		countDown = 0;
	}
	countNum = (countDown / 60);	// 180/60��3�C2�C1�J�E���g������
}

void PadField::FadeOutUpdate(const InputState& input)
{
	fadeValue = 225 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
	}
}

void PadField::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void PadField::Draw()		// ���̕`��
{
	SetFontSize(50);
	DrawField();
	kTime.Draw();
	AnswerCheck();

	// �c���萔��\��
	SetFontSize(40);
	DrawFormatString(960, 170, GetColor(255, 255, 255), "��萔\n  %d", question);
	
	// �|�[�Y�ē��\��
	SetFontSize(20);
	DrawFormatString(900, 720, GetColor(255, 255, 255), "�|�[�Y �E�E�E");

	// �|�[�Y�pSTART�{�^���摜
	DrawGraph(1000, 695, buttonSTARThandle, true);
	
	SetFontSize(50);

	// �������g��
	SetFontSize(100);

	if (countNum != 0)	// countNum��0�ł͂Ȃ������琔�������炵�Ȃ���\������
	{
		SetFontSize(200);
		ChangeFont("Franklin Gothic Medium");	// Franklin Gothic Medium�ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g

		DrawFormatString(740, 350, GetColor(255, 255, 127), "%d", countNum);

		ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	// UD �f�W�^�� ���ȏ��� NK-B�ɕύX
		ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g
	}
	if (countDown == 0)	// �J�E���g��0�ɂȂ��������\��
	{
		// ���
		switch (num)
	{
		// ***�ʏ���***

	case 1:
		// �\�����镶��
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "Y");
		break;

	case 2:
		// �\�����镶��
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "A");
		break;

	case 3:
		// �\�����镶��
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "X");
		break;

	case 4:
		// �\�����镶��
		DrawFormatString(mozi0X, mozi0Y, GetColor(255, 255, 255), "B");
		break;

		// ***����Ȃ����***

	case 5:
		// �\�����镶��
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "Y");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "����Ȃ�");
		break;

	case 6:
		// �\�����镶��
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "A");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "����Ȃ�");
		break;

	case 7:
		// �\�����镶��
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "X");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "����Ȃ�");
		break;

	case 8:
		// �\�����镶��
		DrawFormatString(mozi1X, mozi1Y, GetColor(255, 255, 255), "B");
		DrawFormatString(mozi2X, mozi2Y, GetColor(255, 255, 255), "����Ȃ�");
		break;
	}
	}

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PadField::DrawField()		// �t�B�[���h�̕`��
{
	// �w�i�`��
	DrawGraph(0, 0, handle, true);

	// �t�B�[���h�̕`��
	DrawBox(500, 150, 1100, 750, GetColor(0, 0, 0), true);
	DrawBox(500, 150, 1100, 750, GetColor(255, 255, 255), false);

	SetFontSize(100);
	DrawFormatString(750, 150, GetColor(225, 225, 225), "��");

	DrawFormatString(750, 665, GetColor(225, 225, 225), "��");

	DrawFormatString(1008, 400, GetColor(225, 225, 225), "��");

	DrawFormatString(492, 400, GetColor(225, 225, 225), "��");
}

// �s�����̏ꍇ�̏���(�ʏ�ver)
void PadField::MissPressY()	// ������Y�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
		Pad::isTrigger(PAD_INPUT_3))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::MissPressA()	// ������A�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::MissPressX()	// ������X�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::MissPressB()	// ������B�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_3) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

// �s�����̏ꍇ�̏���(����Ȃ�ver)
void PadField::NotPressY()	// ���̓�����Y�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::NotPressA()	// ���̓�����A�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::NotPressX()	// ���̓�����X�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::NotPressB()	// ���̓�����A�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		// �s����pSE�̓ǂݍ���
		seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

		// SE���Ăяo��
		PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

		// �s����p�o�c�摜�\��
		DrawGraph(900, 550, batuHandle, true);

		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
	//	DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

// �^�C���A�b�v�̏ꍇ�̏���(���Q�[���I�[�o�[)
void PadField::TimeUp()
{
	// �s����pSE�̓ǂݍ���
	seButtonNo = LoadSoundMem("data/BGM/FuseikaiSE.mp3");

	// SE�̉��ʂ𒲐�����
	ChangeVolumeSoundMem(255 * 60 / 100, seButtonNo);

	// SE���Ăяo��
	PlaySoundMem(seButtonNo, DX_PLAYTYPE_BACK, false);

	updateFunc = &PadField::FadeOutUpdate;
}

// �����̓���
bool PadField::AnswerCheck()
{

	SetFontSize(50);

	// true�������琳�𐳉��{�^�����������܂ł͑ҋ@
	if (answerCheck == true)
	{
		// ����pSE�̓ǂ݂���
		seButtonYes = LoadSoundMem("data/BGM/SeikaiSE.mp3");

		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButtonYes);

		// SE���Ăяo��
		PlaySoundMem(seButtonYes, DX_PLAYTYPE_BACK, false);

		// ����p�}���摜
		DrawGraph(900, 550, maruHandle, true);

	//	DrawFormatString(0, 350, GetColor(255, 255, 255), "�Z");
	}
	else
	{
	//	DrawFormatString(0, 300, GetColor(255, 255, 255), "�ҋ@��");
	}
	return false;
}

bool PadField::AnswerFlag()
{
	if (answerCheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

