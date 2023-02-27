#include "PadGameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PadField.h"
#include "Pad.h"
#include <time.h>		// �����_���p
#include "DxLib.h"

void PadGameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &PadGameoverScene::NormalUpdate;
		fadeValue = 0;
	}
}

void PadGameoverScene::NormalUpdate(const InputState& input)
{
	// �^�C�g���̏ꍇ
	if (input.IsTriggred(InputType::title))
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
	// ���X�^�[�g�̏ꍇ
	if (input.IsTriggred(InputType::prev))
	{
		manager_.CangeScene(new PadField(manager_));
		return;
	}
}

void PadGameoverScene::FadeOutUpdate(const InputState& input)
{

}

PadGameoverScene::PadGameoverScene(SceneManager& manager) : Scene(manager),
updateFunc(&PadGameoverScene::FadeInUpdate)
{
	// �摜�̃��[�h
	gameoverHandle = LoadGraph("data/OverBack.png");
	starHandle1 = LoadGraph("data/png/star1.png");
	starHandle2 = LoadGraph("data/png/star2.png");
	starHandle3 = LoadGraph("data/png/star3.png");
}

PadGameoverScene::~PadGameoverScene()
{
	// �摜�̃f���[�g
	DeleteGraph(gameoverHandle);
	DeleteGraph(starHandle1);
	DeleteGraph(starHandle2);
	DeleteGraph(starHandle3);
}

void PadGameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void PadGameoverScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, gameoverHandle, true);

	//	printfDx("%d\n", left);	// �f�o�b�N�p
	srand((unsigned int)time(NULL));	// ���ݎ����̏��ŏ�����
	starnum = rand() % randomnum + 1;		// 1�`3�̗������o��
	starX = rand() % 1400 + 192;	// 192�`1400�̃����_���Ȑ��l (��ʓ��ɕ`��)
	starY = rand() % 650 + 192;	// 192�`700�̃����_���Ȑ��l (��ʓ��ɕ`��)


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
	DrawFormatString(0, 200, GetColor(255, 255, 255), "��:% d\n", starnum);
	// �t���[����(�f�o�b�N�p)
	DrawFormatString(0, 300, GetColor(255, 255, 255), "�t���[��:% d\n", frameCount);

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

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Pad�Q�[���I�[�o�[");
	DrawFormatString(500, 500, GetColor(255, 255, 255), "�^�C�g����BACK\n���X�^�[�g��LB");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
