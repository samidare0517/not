#include "TimeBar.h"
#include "DxLib.h"
#include "game.h"
#include "KeyField.h"
#include "PadField.h"

namespace
{
	bool timeflag = false;
	KeyField* kkey;
	PadField* kpad;
}

TimeBar::TimeBar()
{
	
}	

TimeBar::~TimeBar()
{
	DeleteGraph(handle);
	DeleteGraph(timeBackHandle);
}

void TimeBar::Init()
{
	tb = 1100;		// �^�C���o�[�̑傫��
	time = 3;		// �\���p�̃^�C�}�[(3�b)
	handle = LoadGraph("data/tb.png");	// �^�C���o�[�p�摜
	timeBackHandle = LoadGraph("data/TimeBack.png");	// �^�C���o�[�p�̉摜
}

void TimeBar::Update()
{
	// �����������ꂽ��^�C���o�[����ʃT�C�Y�ɖ߂�
	if (kkey->AnswerFlag() == true)
	{
		tb = 1100;
		time = 3;
	}

	if (kpad->AnswerFlag() == true)
	{
		tb = 1100;
		time = 3;
	}

	timeflag = false;		// �t���O�̏�����


	frame++;
	// �t���[���v�Z
	if (frame >= 60)
	{
		frame = 0;
		if (tb > 0)
		{
			tb -= 200;			// 1�t���[����200�����炷(1�₠�����3�b)
			time--;				// �\������p�̎���
		}
		if (tb <= 500)			// 500�ɂȂ�����500������
		{
			tb = 500;
			timeflag = true;	// 500�ɂȂ�����true��Ԃ�
		}
	}
}

void TimeBar::Draw()
{
	// �������}�C�i�X����(�f�o�b�N�p)
//	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	SetFontSize(40);
	// �Q�[�W�p�̃^�C�}�[(�\���p)
	DrawFormatString(510, 170, GetColor(255, 255, 255), "�c�莞��\n   %d�b", time);
	
	// �^�C���o�[�̔w�i
	DrawGraph(450, 25, timeBackHandle, true);

	// �^�C���o�[
	DrawExtendGraph(500, 100, tb, 0 + 50, handle, true);
}

bool TimeBar::Check()
{
	if (timeflag == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
