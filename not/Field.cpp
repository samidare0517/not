#include "Field.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "GameoverScene.h"
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
	int moziX = 400;
	int moziY = 400;

	bool answercheck = false;

	// �����J��Ԃ���
	int questionnum = 30;
	int i = 0;

	TimeBar kTime;
}

void Field::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 225 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &Field::NormalUpdate;
	}
}

Field::Field(SceneManager& manager) :Scene(manager),
updateFunc_(&Field::FadeInUpdate)
{
	Init();
}

Field::~Field()
{
}

void Field::Init()
{
	kTime.Init();
	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
	num = rand() % randomnum + 1;		// 1�`4�̗������o��
}

void Field::NormalUpdate(const InputState& input)
{
	Pad::update();
	kTime.Update();

	if (answercheck == true)	// �����������ꂽ�玟�̖���
	{
		for (int i = 0; i < questionnum; i++)		// 20��J��Ԃ�
		{
			num = rand() % randomnum + 1;
		}
		i++;

	}
	SetFontSize(50);
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


	if (input.IsTriggred(InputType::next))
	{
		updateFunc_ = &Field::FadeOutUpdate;
		fadeColor_ = 0x000000;
	}
	if (input.IsTriggred(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}

}

void Field::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 225 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (++fadeTimer_ == fade_interval)
	{
		manager_.CangeScene(new GameoverScene(manager_));
		return;
	}
}

void Field::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void Field::Draw()		// ���̕`��
{
	SetFontSize(50);
	DrawField();
	kTime.Draw();
	AnswerCheck();

	SetFontSize(100);
	// �������g��
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

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);

	// ��ʑS�̂�^�����ɓh��Ԃ�
	DrawBox(0, 0, 900, 900, GetColor(255, 255, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Field::DrawField()		// �t�B�[���h�̕`��
{
	SetFontSize(100);
	DrawFormatString(400, 150, GetColor(225, 225, 225), "��");

	DrawFormatString(400, 650, GetColor(225, 225, 225), "��");

	DrawFormatString(650, 400, GetColor(225, 225, 225), "��");

	DrawFormatString(150, 400, GetColor(225, 225, 225), "��");

	// �t�B�[���h�̕`��
	DrawBox(150, 150, 750, 750, GetColor(255, 225, 255), false);
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

