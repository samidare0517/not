#include "TimeBar.h"
#include "KeyField.h"
#include "ExplanationScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void ExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &ExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void ExplanationScene::NormalUpdate(const InputState& input)
{
	// ���փ{�^���������ꂽ�玟�̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::next))
	{
		updateFunc_ = &ExplanationScene::FadeOutUpdate;
	}
}

void ExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void ExplanationScene::Function()
{
}

ExplanationScene::ExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&ExplanationScene::FadeInUpdate)
{
	// �摜�̃��[�h
}

ExplanationScene::~ExplanationScene()
{
	// �摜�̃f���[�g
}

void ExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void ExplanationScene::Draw()
{
	// ���ʂ̕`��
	//DrawRotaGraph(320, 240, 1.0f, 0.0f, titleH_, true);
	DrawBox(200, 200, 400, 400, GetColor(255, 255, 255), true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�������");
	DrawFormatString(0, 500, GetColor(255, 255, 255), 
		"(������)\n"
		"�^�񒆂ɕ\�������w���̒ʂ��\n�p�b�h�̏\���L�[��{�^���������Ă��������B\n"
		"�E���ڂ͕���\n�E���ڂ̓{�^��\n�E�O��ڂ͕����ƃ{�^���̃~�b�N�X�ł��B\n"
		"�Q�[�����X�^�[�g����ɂ�RB�{�^���������Ă��������B");

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂�ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(30, 144, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
