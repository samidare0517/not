#include "GameClearScene.h"
#include "InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Field.h"
#include "DxLib.h"

void GameClearScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameClearScene::NormalUpdate;
		fadeValue_ = 0;
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
updateFunc_(&GameClearScene::FadeInUpdate)
{
	// �摜�̃��[�h
}

GameClearScene::~GameClearScene()
{
	// �摜�̃f���[�g(DeleteGraph(���������摜�n���h��))
}

void GameClearScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameClearScene::Draw()
{
	DrawBox(200, 200, 400, 400, GetColor(255, 0, 255), true);

	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[���N���A");

	SetFontSize(50);
	DrawFormatString(200, 400, GetColor(255, 255, 255),
		"���X�^�[�g���X�y�[�X�L�[\n�^�C�g���@���G���^�[�L�[");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}