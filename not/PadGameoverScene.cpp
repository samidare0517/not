#include "PadGameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PadField.h"
#include "Pad.h"
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
}

PadGameoverScene::~PadGameoverScene()
{
	// �摜�̃f���[�g
	DeleteGraph(gameoverHandle);
}

void PadGameoverScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void PadGameoverScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, gameoverHandle, true);

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Pad�Q�[���I�[�o�[");
	DrawFormatString(500, 500, GetColor(255, 255, 255), "�^�C�g����BACK\n���X�^�[�g��LB");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
