#include "GameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Field.h"
#include "DxLib.h"

void GameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue = 255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval);
	if (--fadeTimer == 0)
	{
		updateFunc = &GameClearScene::NormalUpdate;
		fadeValue = 0;
	}
}

void GameClearScene::NormalUpdate(const InputState& input)
{
	// �^�C�g���̏ꍇ
	if (input.IsTriggred(InputType::next))
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
	// ���X�^�[�g�̏ꍇ
	if (input.IsTriggred(InputType::prev))
	{
		manager_.CangeScene(new Field(manager_));
		return;
	}
}

void GameClearScene::FadeOutUpdate(const InputState& input)
{

}

GameClearScene::GameClearScene(SceneManager& manager) : Scene(manager),
updateFunc(&GameClearScene::FadeInUpdate)
{
	// �摜�̃��[�h
	gameclearHandle = LoadGraph("data/ClearBack.png");
}

GameClearScene::~GameClearScene()
{
	// �摜�̃f���[�g
	DeleteGraph(gameclearHandle);
}

void GameClearScene::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void GameClearScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, gameclearHandle, true);

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[���N���A");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}