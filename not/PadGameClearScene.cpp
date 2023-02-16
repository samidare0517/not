#include "PadGameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PadField.h"
#include "MixField.h"
#include "DxLib.h"

void PadGameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &PadGameClearScene::NormalUpdate;
		fadeValue = 0;
	}
}

void PadGameClearScene::NormalUpdate(const InputState& input)
{
	// �^�C�g���̏ꍇ
	if (input.IsTriggred(InputType::title))
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
	// ���̖��ɐi�ޏꍇ
	if (input.IsTriggred(InputType::next))
	{
		manager_.CangeScene(new MixField(manager_));
		return;
	}
	// ���X�^�[�g�̏ꍇ
	if (input.IsTriggred(InputType::prev))
	{
		manager_.CangeScene(new PadField(manager_));
		return;
	}
}

void PadGameClearScene::FadeOutUpdate(const InputState& input)
{

}

PadGameClearScene::PadGameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&PadGameClearScene::FadeInUpdate)
{
	// �摜�̃��[�h
//	gameclearHandle = LoadGraph("data/ClearBack.png");
}

PadGameClearScene::~PadGameClearScene()
{
	// �摜�̃f���[�g
//	DeleteGraph(gameclearHandle);
}

void PadGameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void PadGameClearScene::Draw()
{
	// ���ʂ̕`��
//	DrawGraph(0, 0, gameclearHandle, true);

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "pad�Q�[���N���A");
	DrawFormatString(500, 500, GetColor(255, 255, 255),
		"�^�C�g����T\n���̖�聨�G���^�[\n���X�^�[�g���X�y�[�X");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}