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
	// �����_���p
	int num = 0;

	// �S�̖̂��o���G�[�V������
	int randomnum = 8;

	// ���̕����\���ʒu
	int mozi0X = 765;	// �ʏ�p
	int mozi0Y = 400;	// �ʏ�p

	int mozi1X = 765;	// ����Ȃ��p��s��
	int mozi1Y = 350;	// ����Ȃ��p��s��

	int mozi2X = 640;	// ����Ȃ��p��s��
	int mozi2Y = 450;	// ����Ȃ��p��s��

	bool answerCheck = false;

	// �����J��Ԃ���
	int questionNum = 30;

	// ���̐�����
	int answerNum = 0;

	// �w�i�p�n���h��
	int handle = 0;

	TimeBar kMixTime;
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
}

void PadField::Init()
{
	handle = LoadGraph("data/Back.png");	// �^�C���o�[�p�摜

	kMixTime.Init();

	answerNum = 0;	// ���̐��𐔃J�E���g��0�ɂ���(������)

	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
	num = rand() % randomnum + 1;		// 1�`8�̗������o��
}

void PadField::NormalUpdate(const InputState& input)
{

	// �w�i�`�� (�f�o�b�N������������悤�ɔw�i��\��)
	DrawGraph(0, 0, handle, true);

	Pad::Update();
	kMixTime.Update();

	if (answerCheck == true)	// �����������ꂽ�玟�̖���
	{
		for (int i = 0; i < questionNum; i++)		// 30��J��Ԃ�
		{
			num = rand() % randomnum + 1;
		}
		answerNum++;
	}
	else if (kMixTime.Check() == true)	// �^�C���o�[��0�ɂȂ��Ă�����Q�[���I�[�o�[������
	{
		TimeUp();
	}

	// ���𐔂�30�ɂȂ�����N���A��ʂ�
	SetFontSize(50);
	if (answerNum == 1)
	{
		answerCheck = false;	// �����̃t���O�̏�����

		// �w��̉񐔐���������Q�[���N���A�V�[���ɍs��
		manager_.CangeScene(new PadGameClearScene(manager_));
		return;
	}
	// �f�o�b�N�p
	DrawFormatString(0, 400, GetColor(255, 255, 255), "��萔:%d", answerNum);

	answerCheck = false;	// �����̃t���O�̏�����

	// �����_���ɂȂ��Ă��邩���ׂ�(�f�o�b�N�p)
	DrawFormatString(0, 200, GetColor(255, 255, 255), "���:% d", num);

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// num�Ɠ���������������Ă����玟�̖���
	// num��1�L�[�̏オ�������܂�false(�ҋ@)

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


	// P�L�[�Ń|�[�Y�V�[��
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}
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
	kMixTime.Draw();
	AnswerCheck();

	// �������g��
	SetFontSize(100);

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

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂�ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(30, 144, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PadField::DrawField()		// �t�B�[���h�̕`��
{
	// �w�i�`��
//	DrawGraph(0, 0, handle, true);

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
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::MissPressA()	// ������A�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_2) || Pad::isTrigger(PAD_INPUT_3) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::MissPressX()	// ������X�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::MissPressB()	// ������B�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_3) ||
		Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

// �s�����̏ꍇ�̏���(����Ȃ�ver)
void PadField::NotPressY()	// ���̓�����Y�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::NotPressA()	// ���̓�����A�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::NotPressX()	// ���̓�����X�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void PadField::NotPressB()	// ���̓�����A�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		manager_.CangeScene(new PadGameoverScene(manager_));
		return;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

// �^�C���A�b�v�̏ꍇ�̏���(���Q�[���I�[�o�[)
void PadField::TimeUp()
{
	manager_.CangeScene(new PadGameoverScene(manager_));
	return;
}

// �����̓���
bool PadField::AnswerCheck()
{

	SetFontSize(50);

	// true�������琳�𐳉��{�^�����������܂ł͑ҋ@
	if (answerCheck == true)
	{
		DrawFormatString(0, 350, GetColor(255, 255, 255), "�Z");
	}
	else
	{
		DrawFormatString(0, 300, GetColor(255, 255, 255), "�ҋ@��");
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
