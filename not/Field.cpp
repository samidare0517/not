#include "Field.h"
#include "DxLib.h"
#include "Pad.h"
#include <time.h>		// �����_���p
#include"TimeBar.h"

namespace
{
	// �����_���p
	int num = 0;

	// ��萔
	int randomnum = 4;

	// ���̕����\���ʒu
	int moziX = 350;
	int moziY = 350;

	//bool gameend = false;
	bool answercheck = false;


	// �����J��Ԃ���
	int questionnum = 20;
	int i = 0;

	TimeBar kTime;
}


Field::Field() 
{

}

Field::~Field()
{

}

void Field::Init()
{
	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����

	num = rand() % randomnum + 1;		// 1�`4�̗������o��
}

void Field::Update()
{

	answercheck = false;	// �����̃t���O�̏�����
	

	if (kTime.Check() == true)	// �t���O��true�������烉���_���ɖ����o��
	{
		num = rand() % randomnum + 1;
	}



	for (i = 0; i < questionnum; i++);
	DrawFormatString(0, 260, GetColor(255, 255, 255), "�J��Ԃ���:% d", i);
	
	
	// �����_���ɂȂ��Ă��邩���ׂ�(�f�o�b�N�p)
	DrawFormatString(0, 100, GetColor(255, 255, 255), "���:% d", num);

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// num�Ɠ���������������Ă����玟�̖���

	// num��1�L�[�̏オ�������܂�false(�ҋ@)
	if (num == 1)
	{
		if (padState & (PAD_INPUT_UP))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressUp();			// �듚�������Ăяo��
		}
		
	}

	if (num == 2)
	{
		if (padState & (PAD_INPUT_DOWN))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressDown();		// �듚�������Ăяo��
		}
	}

	if (num == 3)
	{
		if (padState & (PAD_INPUT_RIGHT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressRight();		// �듚�������Ăяo��
		}
	}

	if (num == 4)
	{
		if (padState & (PAD_INPUT_LEFT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressLeft();		// �듚�������Ăяo��
		}
	}


	// �u����Ȃ��v�e�X�g
	//if (num == 5)
	//{
	//	if (padState & (PAD_INPUT_LEFT))
	//	{
	//		answercheck = false;		// �����������ꂽ��}��
	//	}
	//	else
	//	{
	//		answercheck = true;
	//	}
	//}

}

void Field::Draw()		// ���̕`��
{

	// �������g��
	SetFontSize(100);
	switch (num)	// ���
	{
	case 1:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		break;

	case 2:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		break;

	case 3:;
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "�E");
		break;

	case 4:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		break;

	//case 5:
	//	// �\�����镶��
	//	DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
	//	DrawFormatString(200, 500, GetColor(255, 255, 255), "����Ȃ�");
	//	break;
	

	default:
		break;
	}
}

void Field::DrawField()		// �t�B�[���h�̕`��
{

	DrawFormatString(350, 100, GetColor(225, 225, 225), "��");

	DrawFormatString(350, 600, GetColor(225, 225, 225), "��");

	DrawFormatString(600, 350, GetColor(225, 225, 225), "��");

	DrawFormatString(100, 350, GetColor(225, 225, 225), "��");

	// �t�B�[���h�̕`��
	DrawBox(100, 100, 700, 700, GetColor(255, 255, 255), false);

}

// �s�����̏ꍇ�̏���
void Field::MissPressUp()
{
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_DOWN) || padState & (PAD_INPUT_LEFT) ||
		padState & (PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::MissPressDown()
{
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_UP) || padState & (PAD_INPUT_LEFT) ||
		padState & (PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::MissPressLeft()
{
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_UP) || padState & (PAD_INPUT_DOWN) ||
		padState & (PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::MissPressRight()
{
	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & (PAD_INPUT_UP) || padState & (PAD_INPUT_DOWN) ||
		padState & (PAD_INPUT_LEFT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

// �����̓���
bool Field::AnswerCheck()
{

	SetFontSize(50);
	
	// true�������琳�𐳉��{�^�����������܂ł͑ҋ@
	if (answercheck == true)
	{
		DrawFormatString(0, 200, GetColor(255, 255, 255), "�Z");
	}
	else
	{
		DrawFormatString(0, 150, GetColor(255, 255, 255), "�ҋ@��");
	}
	return false;
}



// �Q�[�����I�����Ă��邩���s���Ă��邩���ׂ�
//bool Field::isGameEnd()
//{
//	SetFontSize(50);
//
//	if(gameend == true)
//	{
//		// �G���h�V�[���֍s��
//		DrawFormatString(0, 200, GetColor(255, 255, 255), "�I��");
//	}
//	else
//	{
//		// �Q�[�����s
//		DrawFormatString(0, 200, GetColor(255, 255, 255), "���s");
//	}
//	return false;
//}