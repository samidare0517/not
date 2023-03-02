#include "TimeBar.h"
#include "KeyField.h"
#include "KeyExplanationScene.h"
#include "GameExplanation.h"
#include "InputState.h"
#include "SceneManager.h"
#include "DxLib.h"


void KeyExplanationScene::FadeInUpdate(const InputState& input)
{
	fadeValue = fadeTimer;
	if (--fadeTimer == 0)
	{
		updateFunc_ = &KeyExplanationScene::NormalUpdate;
		fadeValue = 0;
	}
}

void KeyExplanationScene::NormalUpdate(const InputState& input)
{
	// �{�^���������ꂽ��Q�[���V�[���ֈڍs����
	if (input.IsTriggred(InputType::next))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc_ = &KeyExplanationScene::FadeOutUpdate;
	}
	// RB�{�^���������ꂽ��Q�[�������̃V�[���ֈڍs����
	if (input.IsTriggred(InputType::button))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);
		updateFunc_ = &KeyExplanationScene::FadeOutUpdate2;
	}
}

void KeyExplanationScene::FadeOutUpdate(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void KeyExplanationScene::FadeOutUpdate2(const InputState& input)
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new GameExplanation(manager_));
		return;
	}
}

void KeyExplanationScene::Function()
{
}

KeyExplanationScene::KeyExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&KeyExplanationScene::FadeInUpdate)
{
	// �摜�̃��[�h
	Handle = LoadGraph("data/KeyGameSetumei.png");

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

KeyExplanationScene::~KeyExplanationScene()
{
	// �摜�̃f���[�g
	DeleteGraph(Handle);

	// ���y�̃f���[�g
	DeleteSoundMem(seButton);
}

void KeyExplanationScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void KeyExplanationScene::Draw()
{
	// ���ʂ̕`��
	DrawGraph(0, 0,Handle, true);

	SetFontSize(30);
	DrawFormatString(20, 20, GetColor(255, 255, 77),
		"RB�{�^���ŃQ�[������");

	SetFontSize(50);
	DrawFormatString(550, 410, GetColor(127, 255, 127), 
		"1��ڂ͕������ł�");
	DrawFormatString(350, 500, GetColor(255, 255, 255),
		"�\���L�[�����X�e�B�b�N���g�p���Ă�������");
	
	// �_�ŏ���
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		SetFontSize(50);
		DrawFormatString(270, 700, GetColor(255, 255, 255),"�Q�[�����X�^�[�g����ɂ�");
		DrawFormatString(820, 700, GetColor(255, 77, 77),"A�{�^��");
		DrawFormatString(995, 700, GetColor(255, 255, 255),"�������Ă�������");
	}
	
	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
