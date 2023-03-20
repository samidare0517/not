#include "GameSelect.h"
#include "InputState.h"
#include "SceneManager.h"
#include "KeyExplanationScene.h"
#include "PadExplanationScene.h"
#include "MixExplanationScene.h"
#include "TitleScene.h"
#include "DxLib.h"

void GameSelect::FadeInUpdate(const InputState& input)
{
	fadeValue = static_cast<int>(255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval));
	if (--fadeTimer == 0)
	{
		updateFunc = &GameSelect::NormalUpdate;
		fadeValue = 0;
	}
}

void GameSelect::NormalUpdate(const InputState& input)
{
	// �L�[���̏ꍇ
	if (input.IsTriggred(InputType::next))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &GameSelect::FadeOutUpdate;
	}

	// �{�^�����̏ꍇ
	if (input.IsTriggred(InputType::prev))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		
		updateFunc = &GameSelect::FadeOutUpdate2;
	}
	
	// �~�b�N�X���̏ꍇ
	if (input.IsTriggred(InputType::next2))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &GameSelect::FadeOutUpdate3;
	}
	
	// �����ɖ߂�
	if (input.IsTriggred(InputType::RBbutton))
	{
		// SE�̉��ʂ𒲐�����
		ChangeVolumeSoundMem(255 * 60 / 100, seButton);

		// SE���Ăяo��
		PlaySoundMem(seButton, DX_PLAYTYPE_BACK, false);

		updateFunc = &GameSelect::FadeOutUpdate4;
	}
}

void GameSelect::FadeOutUpdate(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval)));
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new KeyExplanationScene(manager_));
		return;
	}
}

void GameSelect::FadeOutUpdate2(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval)));
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new PadExplanationScene(manager_));
		return;
	}
}

void GameSelect::FadeOutUpdate3(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval)));
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new MixExplanationScene(manager_));
		return;
	}
}

void GameSelect::FadeOutUpdate4(const InputState& input)
{
	fadeValue = static_cast<int>(255 * (static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval)));
	if (++fadeTimer == fadeInterval)
	{
		manager_.CangeScene(new TitleScene(manager_));
		return;
	}
}

GameSelect::GameSelect(SceneManager& manager) : Scene(manager),
updateFunc(&GameSelect::FadeInUpdate)
{
	backScreenHandle = LoadGraph("data/KeyGameSetumei.png");
	buttonAhandle = LoadGraph("data/button/buttonA.png");
	buttonBhandle = LoadGraph("data/button/buttonB.png");
	buttonXhandle = LoadGraph("data/button/buttonX.png");
	buttonRBHandle = LoadGraph("data/button/buttonRB.png");

	// SE�̓ǂݍ���
	seButton = LoadSoundMem("data/BGM/NextSE.mp3");
}

GameSelect::~GameSelect()
{
	DeleteGraph(backScreenHandle);
	DeleteGraph(buttonAhandle);
	DeleteGraph(buttonBhandle);
	DeleteGraph(buttonXhandle);
	DeleteGraph(buttonRBHandle);
	DeleteSoundMem(seButton);
}

void GameSelect::Update(const InputState& input)
{
	(this->*updateFunc)(input);
}

void GameSelect::Draw()
{
	DrawGraph(0, 0, backScreenHandle, true);
	DrawGraph(950, 460, buttonAhandle, true);
	DrawGraph(950, 560, buttonBhandle, true);
	DrawGraph(950, 660, buttonXhandle, true);
	DrawGraph(1100, 825, buttonRBHandle, true);

	SetFontSize(100);
	DrawFormatString(450, 200, GetColor(255, 255, 255), "�X�e�[�W�Z���N�g");
	SetFontSize(50);
	DrawFormatString(530, 500, GetColor(255, 255, 255), "�������");
	DrawFormatString(520, 600, GetColor(255, 255, 255), "�{�^�����");
	DrawFormatString(500, 700, GetColor(255, 255, 255), "�~�b�N�X���");

	DrawFormatString(850, 500, GetColor(255, 255, 255), "�E�E�E");
	DrawFormatString(850, 600, GetColor(255, 255, 255), "�E�E�E");
	DrawFormatString(850, 700, GetColor(255, 255, 255), "�E�E�E");

	SetFontSize(30);
	DrawFormatString(1050, 850, GetColor(255, 255, 77), "�߂�");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}