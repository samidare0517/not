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
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new KeyField(manager_));
		return;
	}
}

void KeyExplanationScene::FadeOutUpdate2(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeIntarval)));
	if (++fadeTimer == fadeIntarval)
	{
		manager_.CangeScene(new GameExplanation(manager_));
		return;
	}
}

KeyExplanationScene::KeyExplanationScene(SceneManager& manager) : Scene(manager),
updateFunc_(&KeyExplanationScene::FadeInUpdate)
{
	// �摜�̃��[�h
	Handle = LoadGraph("data/KeyGameSetumei.png");
	buttonAhandle = LoadGraph("data/button/buttonA.png");
	buttonRBhandle = LoadGraph("data/button/buttonRB.png");
	buttonPadhandle = LoadGraph("data/button/buttonPad.png");
	buttonLShandle = LoadGraph("data/button/buttonLS.png");

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

KeyExplanationScene::~KeyExplanationScene()
{
	// �摜�̃f���[�g
	DeleteGraph(Handle);
	DeleteGraph(buttonAhandle);
	DeleteGraph(buttonRBhandle);
	DeleteGraph(buttonPadhandle);
	DeleteGraph(buttonLShandle);

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
	DrawGraph(860, 600, buttonRBhandle, true);
	DrawGraph(645, 435, buttonPadhandle, true);
	DrawGraph(810, 440, buttonLShandle, true);


	SetFontSize(40);
	DrawFormatString(660, 620, GetColor(255, 255, 77), "�Q�[������");
	SetFontSize(50);
	DrawFormatString(550, 390, GetColor(127, 255, 127), "1��ڂ͕������ł�");
	DrawFormatString(750, 480, GetColor(255, 255, 255), "OR");
	
	// �_�ŏ���
	static int BrinkCounter;
	BrinkCounter++;
	if (BrinkCounter == 120)
	{
		BrinkCounter = 0;
	}
	if (BrinkCounter < 80)
	{
		DrawGraph(810, 700, buttonAhandle, true);
		DrawFormatString(680, 740, GetColor(255, 255, 77), "PUSH");
	}
	
	// ������e�摜�Ƃ��łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);

	// ��ʑS�̂����ɓh��Ԃ�
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
