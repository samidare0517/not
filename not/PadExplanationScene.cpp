#include "PadExplanationScene.h"
#include "TimeBar.h"
#include "PadField.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void PadExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &PadExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void PadExplanationScene::NormalUpdate(const InputState& input)
{
	// ���փ{�^���������ꂽ�玟�̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::next))
	{
		updateFunc_ = &PadExplanationScene::FadeOutUpdate;
	}
}

void PadExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new PadField(manager_));
		return;
	}
}

void PadExplanationScene::Function()
{
}

PadExplanationScene::PadExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&PadExplanationScene::FadeInUpdate)
{
	// �摜�̃��[�h
	Handle = LoadGraph("data/PadGameSetumei.png");
}

PadExplanationScene::~PadExplanationScene()
{
	// �摜�̃f���[�g
	DeleteGraph(Handle);
}

void PadExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void PadExplanationScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, Handle, true);

//	DrawFormatString(0, 0, GetColor(255, 255, 255), "���ڐ������");
//	DrawFormatString(0, 500, GetColor(255, 255, 255),"(������)\n");

	// �_�ŏ���
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		DrawFormatString(250, 800, GetColor(255, 255, 255), "�Q�[�����X�^�[�g����ɂ�");
		DrawFormatString(790, 800, GetColor(255, 0, 0), "RB�{�^��");
		DrawFormatString(995, 800, GetColor(255, 255, 255), "�������Ă�������");
	}

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
