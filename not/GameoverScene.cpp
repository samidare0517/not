#include "GameoverScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Field.h"
#include "Pad.h"
#include "DxLib.h"

void GameoverScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameoverScene::NormalUpdate;
		fadeValue_ = 0;
	}
}

void GameoverScene::NormalUpdate(const InputState& input)
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

void GameoverScene::FadeOutUpdate(const InputState& input)
{

}

GameoverScene::GameoverScene(SceneManager& manager) : Scene(manager),
updateFunc_(&GameoverScene::FadeInUpdate)
{
	// �摜�̃��[�h
	gameoverH = LoadGraph("data/OverBack.png");
}

GameoverScene::~GameoverScene()
{
	// �摜�̃f���[�g
	DeleteGraph(gameoverH);
}

void GameoverScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameoverScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, gameoverH, true);

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[���I�[�o�[");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

