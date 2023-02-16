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
}

PadExplanationScene::~PadExplanationScene()
{
	// �摜�̃f���[�g
}

void PadExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void PadExplanationScene::Draw()
{
	// ���ʂ̕`��
	//DrawRotaGraph(320, 240, 1.0f, 0.0f, titleH_, true);
	DrawBox(200, 200, 400, 400, GetColor(255, 255, 255), true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "���ڐ������");
	DrawFormatString(0, 500, GetColor(255, 255, 255),
		"(������)\n"
		"���ڂ�A�EB�EX�EY�{�^���������ăv���C���܂��B\n"
		"�Q�[�����X�^�[�g����ɂ�RB�{�^���������Ă��������B");

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂�ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(30, 144, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
