#include "KeyExplanationScene.h"
#include "InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "KeyGameoverScene.h"
#include "DxLib.h"

void TitleScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc = &TitleScene::NormalUpdate;
		fadeValue = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	// ���փ{�^���������ꂽ�玟�̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::next))
	{
		updateFunc = &TitleScene::FadeOutUpdate;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyExplanationScene(manager_));
		return;
	}
}

void TitleScene::Function()
{
}

TitleScene::TitleScene(SceneManager& manager) : Scene(manager),
updateFunc(&TitleScene::FadeInUpdate)
{
	// �摜�̃��[�h
	titleHandle = LoadGraph("data/TitleBack.png");
}

TitleScene::~TitleScene()
{
	// �摜�̃f���[�g
	DeleteGraph(titleHandle);
}

void TitleScene::Update(const InputState& input)
{
	(this ->*updateFunc)(input);
}

void TitleScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, titleHandle, true);
	
	ChangeFont("UD �f�W�^�� ���ȏ��� NK-B");	//UD �f�W�^�� ���ȏ��� NK-B�ɕύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	// �A���`�G�C���A�X�t�H���g
	
	SetFontSize(100);
	DrawFormatString(550, 400, GetColor(255, 255, 255), "�^�C�g��");
	
	// �V�[���m�F�p
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�g��");

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	
	// ��ʑS�̂�ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(30, 144, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
