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
	timeflag = false;		// �t���O�̏�����
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

	frame++;
	// �t���[���v�Z
	if (frame >= 60)
	{
		frame = 0;
		if (tb > 0)
		{
			time--;				// �\������p�̎���
		}
	}

	int Mtime = 3;	// �^�C�}�[�̐���
	int Mtb = 1100;	// �^�C���o�[�̈�ԉE
	float test = ((Mtb - static_cast<float>(500)) / Mtime) / 60;

	if (tb <= 500)
	{
		tb = 500;
	}
	else if (tb >= 500)
	{
		tb -= static_cast<int>(test);
	}
	if (time <= 0)
	{
		time = 0;
	}
	if (tb <= 500)
	{
		timeflag = true;
	}
//	printfDx("tb:%d\n", tb);
//	printfDx("frame:%d\n", frame);
}

void TimeBar::Draw()
{
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
