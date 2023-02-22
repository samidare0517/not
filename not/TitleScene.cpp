#include "KeyExplanationScene.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "KeyGameoverScene.h"
#include <time.h>		// �����_���p
#include "DxLib.h"

void TitleScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc = &TitleScene::NormalUpdate;
		fadeValue = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	// ���փ{�^���������ꂽ�玟�̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::next))
	{
		updateFunc = &TitleScene::FadeOutUpdate;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyExplanationScene(manager_));
		return;
	}
}


TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
updateFunc(&TitleScene::FadeInUpdate)
{
	// �摜�̃��[�h
	titleHandle = LoadGraph("data/TitleBack.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");
}

TitleScene::~TitleScene()
{
	// �摜�̃f���[�g
	DeleteGraph(titleHandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);
}

void TitleScene::Update(const InputState& input)
{
	(this ->*updateFunc)(input);
}


void TitleScene::Draw()
{
	// �w�i�`��
	DrawGraph(0, 0, titleHandle, true);
	
	//	printfDx("%d\n", left);	// �f�o�b�N�p
	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
	starnum = rand() % randomnum + 1;		// 1�`3�̗������o��
	starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
	starY = rand() % 650  + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)

	frameCount++;

	if (frameCount == 3)	//3�t���[�����Ƃɉ摜���E��192�ړ�������
	{
		frameCount = 0;	// �t���[���J�E���g�����Z�b�g
		left += 192;	// 192���v���X����
	}
	if (left == 960)	// �摜�̉E�܂ňړ�����ƍ��ɖ߂�
	{
		left = 0;
		changeY = true;	// �摜������192�ړ�
	}
	if (changeY)	// �摜������192�ړ�
	{
		top += 192;
		changeY = false;
	}
	if (top == 768)
	{
		top = 0;
	}

	// �����_���ɂȂ��Ă��邩(�f�o�b�N�p)
	DrawFormatString(0, 200, GetColor(255, 255, 255), "��:% d", starnum);
	printfDx("%d\n", frameCount);
	
	// �����_���ɃA�j���[�V������`��
	switch (starnum)
	{
	case 1:
		DrawRectRotaGraph(starX, starY,
			left, top, rigth, bottom,
			1, 0, starHandle1, true, false);
		break;

	case 2:
		DrawRectRotaGraph(starX, starY,
			left, top, rigth, bottom,
			1, 0, starHandle2, true, false);
		break;

	case 3:
		DrawRectRotaGraph(starX, starY,
			left, top, rigth, bottom,
			1, 0, starHandle3, true, false);
		break;
	}

	
	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	//UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g
	
	SetFontSize(100);
	DrawFormatString(600, 400, GetColor(255, 255, 255), "�^�C�g��");
	
	// �_�ŏ���
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}

	if (BrinkCounter < 80)
	{
		SetFontSize(50);
		DrawFormatString(500, 600, GetColor(255, 255, 0), "RB�{�^���������Ă�������");
	}

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�g��");

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	
	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
