#include "TimeBar.h"
#include "DxLib.h"
#include "game.h"
#include "Field.h"

namespace
{
	bool timeflag = false;
	Field* kfield;
}

TimeBar::TimeBar()
{
	
}	

TimeBar::~TimeBar()
{
	
}

void TimeBar::Init()
{
	tb = 1100;		// �^�C���o�[�̑傫��
	handle = LoadGraph("data/tb.png");	// �^�C���o�[�p�摜
}

void TimeBar::Update()
{
	// �����������ꂽ��^�C���o�[����ʃT�C�Y�ɖ߂�
	if (kfield->AnswerFlag() == true)
	{
		tb = 1100;
	}

	timeflag = false;		// �t���O�̏�����

	frame++;
	// �t���[���v�Z
	if (frame >= 60)
	{
		frame = 0;
		if (tb > 0)
		{
			tb -= 200;			// 1�t���[����200�����炷(1�₠����3�b)
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
	SetFontSize(50);
	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	DrawExtendGraph(500, 120, tb, 0 + 50, handle, true);
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
