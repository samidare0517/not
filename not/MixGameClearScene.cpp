#include "MixGameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MixField.h"
#include "DxLib.h"

void MixGameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &MixGameClearScene::NormalUpdate;
		fadeValue = 0;
	}
}

void MixGameClearScene::NormalUpdate(const InputState& input)
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
		manager_.CangeScene(new MixField(manager_));
		return;
	}
}

void MixGameClearScene::FadeOutUpdate(const InputState& input)
{

}

MixGameClearScene::MixGameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&MixGameClearScene::FadeInUpdate)
{
	// �摜�̃��[�h
	gameclearHandle = LoadGraph("data/ClearBack.png");
}

MixGameClearScene::~MixGameClearScene()
{
	// �摜�̃f���[�g
	DeleteGraph(gameclearHandle);
}

void MixGameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void MixGameClearScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, gameclearHandle, true);

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Mix�Q�[���N���A");
	DrawFormatString(500, 500, GetColor(255, 255, 255),
		"�^�C�g����BACK\n���X�^�[�g��LB");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}