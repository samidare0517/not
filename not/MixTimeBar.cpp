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

}

void MixTimeBar::Init()
{
	mtb = 1100;		// �^�C���o�[�̑傫��
	time = 4;		// �\���p�̃^�C�}�[(6�b)
	handle = LoadGraph("data/tb.png");	// �^�C���o�[�p�摜
	mixTimeBackHandle = LoadGraph("data/TimeBack.png");	// �^�C���o�[�p�̉摜
	mixTimerBackHandle = LoadGraph("data/TimerBack.png");
}

void MixTimeBar::Update()
{
	// �����������ꂽ��^�C���o�[����ʃT�C�Y�ɖ߂�
	if (kMixField->AnswerFlag() == true)
	{
		mtb = 1100;
		time = 4;
	}

	timeflag = false;		// �t���O�̏�����

	frame++;
	// �t���[���v�Z
	if (frame >= 60)
	{
		frame = 0;
		if (mtb > 0)
		{
			mtb -= 150;			// 1�t���[����200�����炷(1�₠�����4�b)
			time--;				// �\������p�̎���
		}
		if (mtb <= 500)			// 500�ɂȂ�����500������
		{
			mtb = 500;
			timeflag = true;	// 500�ɂȂ�����true��Ԃ�
		}
	}
}

void MixTimeBar::Draw()
{
	// �������}�C�i�X����(�f�o�b�N�p)
	SetFontSize(50);
	//	DrawFormatString(0, 2, GetColor(255, 255, 255), "\nTime:%d\n", tb);

	DrawGraph(20, 20, mixTimerBackHandle, true);

	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	//UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g

	// �Q�[�W�p�̃^�C�}�[(�\���p)
	DrawFormatString(75, 35, GetColor(255, 255, 255), "�c�莞��\n   %d�b", time);

	// �^�C���o�[�̔w�i
	DrawGraph(450, 25, mixTimeBackHandle, true);

	// �^�C���o�[
	DrawExtendGraph(500, 100, mtb, 0 + 50, handle, true);
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
