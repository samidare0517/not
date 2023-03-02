#include "MixExplanationScene.h"
#include "TimeBar.h"
#include "MixField.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void MixExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &MixExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void MixExplanationScene::NormalUpdate(const InputState& input)
{
	// ���փ{�^���������ꂽ�玟�̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::next))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc_ = &MixExplanationScene::FadeOutUpdate;
	}
}

void MixExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new MixField(manager_));
		return;
	}
}

void MixExplanationScene::Function()
{
}

MixExplanationScene::MixExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&MixExplanationScene::FadeInUpdate)
{
	// �摜�̃��[�h
	Handle = LoadGraph("data/KeyGameSetumei.png");

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

MixExplanationScene::~MixExplanationScene()
{
	// �摜�̃f���[�g
	DeleteGraph(Handle);

	// ���y�̃f���[�g
	DeleteSoundMem(seButton);
}

void MixExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void MixExplanationScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0, Handle, true);
	
	SetFontSize(50);
	DrawFormatString(550, 410, GetColor(127, 255, 127),
		"3��ڂ̓~�b�N�X���ł�");
	DrawFormatString(350, 500, GetColor(255, 255, 255),
		"�������̏ꍇ�A�\���L�[�����X�e�B�b�N��");
	DrawFormatString(340, 590, GetColor(255, 255, 255),
		"�{�^�����̏ꍇ�A�{�^�����g�p���Ă�������");


	// �_�ŏ���
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		DrawFormatString(270, 700, GetColor(255, 255, 255), "�Q�[�����X�^�[�g����ɂ�");
		DrawFormatString(820, 700, GetColor(255, 77, 77), "A�{�^��");
		DrawFormatString(995, 700, GetColor(255, 255, 255), "�������Ă�������");
	}

	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
