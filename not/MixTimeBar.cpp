#include "MixTimeBar.h"
#include "MixField.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	bool timeflag = false;
	MixField* kMixField;
}

MixTimeBar::MixTimeBar()
{

}

MixTimeBar::~MixTimeBar()
{
	DeleteGraph(handle);
	DeleteGraph(mixTimeBackHandle);
}

void MixTimeBar::Init()
{
	tb = 1100;		// �^�C���o�[�̑傫��
	time = 4;		// �\���p�̃^�C�}�[(4�b)
	timeflag = false;		// �t���O�̏�����
	handle = LoadGraph("data/tb.png");	// �^�C���o�[�p�摜
	mixTimeBackHandle = LoadGraph("data/TimeBack.png");	// �^�C���o�[�p�̔w�i�摜
}

void MixTimeBar::Update()
{
	// �����������ꂽ��^�C���o�[����ʃT�C�Y�ɖ߂�
	if (kMixField->AnswerFlag() == true)
	{
		tb = 1100;
		time = 4;
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

	int Mtime = 4;	// �^�C�}�[�̐���
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

void MixTimeBar::Draw()
{
	// �������}�C�i�X����(�f�o�b�N�p)
	SetFontSize(40);
	//	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	//UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g

	// �Q�[�W�p�̃^�C�}�[(�\���p)
	DrawFormatString(510, 170, GetColor(255, 255, 255), "�c�莞��\n   %d�b", time);

	// �^�C���o�[�̔w�i
	DrawGraph(450, 25, mixTimeBackHandle, true);

	// �^�C���o�[
	DrawExtendGraph(500, 100, tb, 0 + 50, handle, true);
}

bool MixTimeBar::Check()
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
