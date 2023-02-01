#include "Field.h"
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
	int moziX = 400;
	int moziY = 400;

	

	bool answercheck = false;

	// �����J��Ԃ���
	int questionnum = 30;
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
	Pad::update();
	if (answercheck == true)	// �����������ꂽ�玟�̖���
	{
		for (int i = 0; i < questionnum; i++)		// 20��J��Ԃ�
		{
			num = rand() % randomnum + 1;
		}
		i++;
	}

	// �m�F�p
	if (i == 30)
	{
		DrawFormatString(0, 350, GetColor(255, 255, 255), "�S�␳��:% d", i);
	}
		
	DrawFormatString(0, 300, GetColor(255, 255, 255), "��萔:% d", i);

	answercheck = false;	// �����̃t���O�̏�����

	
	
	// �����_���ɂȂ��Ă��邩���ׂ�(�f�o�b�N�p)
	DrawFormatString(0, 100, GetColor(255, 255, 255), "���:% d", num);

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// num�Ɠ���������������Ă����玟�̖���
	// num��1�L�[�̏オ�������܂�false(�ҋ@)

	// ***�ʏ���***
	// �オ����
	if (num == 1)
	{
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressUp();			// �듚�������Ăяo��
		}
	}

	// ��������
	if (num == 2)
	{
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressDown();		// �듚�������Ăяo��
		}
	}

	// ��������
	if (num == 3)
	{
		if (Pad::isTrigger(PAD_INPUT_LEFT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressLeft();		// �듚�������Ăяo��
		}
	}
	
	// �E������
	if (num == 4)
	{
		if (Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			MissPressRight();		// �듚�������Ăяo��
		}
	}
	
	// ***����Ȃ����***
	
	// �ザ��Ȃ��@(�����E����)
	if (num == 5)
	{
		if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) || 
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			NotPressUp();		// �듚�������Ăяo��
		}
	}

	 //������Ȃ��@(�㍶�E����)
	if (num == 6)
	{
		if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_LEFT) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			NotPressDown();		// �듚�������Ăяo��
		}
	}

	// ������Ȃ��@(�㉺�E����)
	if (num == 7)
	{
		if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
			Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			NotPressLeft();		// �듚�������Ăяo��
		}
	}

	// �E����Ȃ��@(�㉺������)
	if (num == 8)
	{
		if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
			Pad::isTrigger(PAD_INPUT_LEFT))
		{
			answercheck = true;		// �����������ꂽ��}��
		}
		else
		{
			NotPressRight();		// �듚�������Ăяo��
		}
	}
}

void Field::Draw()		// ���̕`��
{

	// �������g��
	SetFontSize(100);
	switch (num)	// ���
	{
		// ***�ʏ���***

	case 1:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		break;

	case 2:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		break;

	case 3:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		break;

	case 4:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "�E");
		break;

		// ***����Ȃ����***

	case 5:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "����Ȃ�");
		break;
	
	case 6:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "����Ȃ�");
		break;
	
	case 7:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "��");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "����Ȃ�");
		break;

	case 8:
		// �\�����镶��
		DrawFormatString(moziX, moziY, GetColor(255, 255, 255), "�E");
		DrawFormatString(250, 500, GetColor(255, 255, 255), "����Ȃ�");
		break;
	}
}

void Field::DrawField()		// �t�B�[���h�̕`��
{

	DrawFormatString(400, 150, GetColor(225, 225, 225), "��");

	DrawFormatString(400, 650, GetColor(225, 225, 225), "��");

	DrawFormatString(650, 400, GetColor(225, 225, 225), "��");

	DrawFormatString(150, 400, GetColor(225, 225, 225), "��");

	// �t�B�[���h�̕`��
	DrawBox(150, 150, 750, 750, GetColor(255, 255, 255), false);

}

// �s�����̏ꍇ�̏���(�ʏ�ver)

void Field::MissPressUp()	// ��������̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_DOWN) || Pad::isTrigger(PAD_INPUT_LEFT) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::MissPressDown()	// ���������̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_LEFT) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::MissPressLeft()	// ���������̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
		Pad::isTrigger(PAD_INPUT_RIGHT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::MissPressRight()	// �������E�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_UP) || Pad::isTrigger(PAD_INPUT_DOWN) ||
		Pad::isTrigger(PAD_INPUT_LEFT))
	{
	//	gameend = true;
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

// �s�����̏ꍇ�̏���(����Ȃ�ver)

void Field::NotPressUp()	// ���̓�������ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::NotPressDown()	// ���̓��������ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::NotPressLeft()	// ���̓��������ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		// �f�o�b�N�p
		DrawFormatString(0, 220, GetColor(255, 255, 255), "�~");
	}
}

void Field::NotPressRight()	// ���̓������E�ȊO�̏ꍇ
{
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
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
		//if (kTime.Check() == false)	// �t���O��true�������烉���_���ɖ����o��
		//{
		//	kTime.Update();
		//}
		DrawFormatString(0, 200, GetColor(255, 255, 255), "�Z");
	}
	else
	{
		DrawFormatString(0, 150, GetColor(255, 255, 255), "�ҋ@��");
	}
	return false;
}

bool Field::AnswerFlag()
{
	if (answercheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}
	
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