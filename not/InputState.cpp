#include "InputState.h"
#include "DxLib.h"
#include <cassert>

InputState::InputState()
{
	// ����
	defaultMapTable[InputType::next] = { {InputCategory::pad,PAD_INPUT_Z} };//RB�{�^��

	// �O��
	defaultMapTable[InputType::prev] = { {InputCategory::pad,PAD_INPUT_Y} };//LB�{�^��

	// �^�C�g����
	defaultMapTable[InputType::title] = { {InputCategory::pad,PAD_INPUT_L} };//BACK�{�^��

	// �|�[�Y
	defaultMapTable[InputType::pause] = { {InputCategory::pad,PAD_INPUT_R} };//START�{�^��
										

	inputMapTable = defaultMapTable;

	// �ꎞ�}�b�v�e�[�u���ɃR�s�[
	tempMapTable = inputMapTable;
	
	currentInput.resize(static_cast<int>(InputType::max));
	lastInput.resize(static_cast<int>(InputType::max));
}

void InputState::Update()
{
	lastInput = currentInput;	// ���O�̓��͏����L�����Ă���
	
	char keystate[256];

	GetHitKeyStateAll(keystate);	// �S�L�[���擾

	int padState = GetJoypadInputState(DX_INPUT_PAD1);	// �p�b�h1�R���̏��𓾂�
	
	for (const auto& keymap : inputMapTable)
	{
		for (const auto& input : keymap.second)
		{
			// ���͏��z������[�v����B����Input�̒��g�́Akeybd,KEY_INPUT_RETURN�Ȃǂ�
			// �Z�b�g(InputInfo)�������Ă���Bkeymap.first�ɂ́A�Ή�����Q�[�����͖���
			// "InputType::next"�Ȃǂ������Ă���B

			if (input.cat == InputCategory::pad)
			{
				currentInput[static_cast<int>(keymap.first)] = keystate[input.id];
			}

			// ���͂̂����ǂꂩ��true������������u���͂���Ă���v
			// �Ƃ݂Ȃ���break����

			if (currentInput[static_cast<int>(keymap.first)])
			{
				break;
			}
		}

	}
}

void InputState::RewriteInputInfo(InputType type, InputCategory cat, int id)
{
	// ���͎��(������)���Ȃ���Ζ����Ȃ̂Ŗ���
	if (tempMapTable.count(type) == 0)
	{
		return;
	}

	bool isRewrite = false;
	for (auto& InputInfo : tempMapTable[type])
	{
		if (InputInfo.cat == cat)
		{
			// �J�e�S�����q�b�g������ID���㏑������
			InputInfo.id = id;
			isRewrite = true;
			break;
		}
	}
	if (!isRewrite)
	{
		// �����J�e�S�������݂��Ȃ�������A�����Œǉ����Ă���
		tempMapTable[type].push_back({ cat,id });
	}

}

bool InputState::IsTriggred(InputType type) const
{
	return currentInput[static_cast<int>(type)];
}

bool InputState::IsPressed(InputType type) const
{
	return IsPressed(type) && !lastInput[static_cast<int>(type)];
}

