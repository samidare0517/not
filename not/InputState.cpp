#include "InputState.h"
#include "DxLib.h"
#include <cassert>

InputState::InputState()
{
	// 次へ
	defaultMapTable[InputType::next] = { {InputCategory::keybd,PAD_INPUT_6} };
									
	// 前へ
	defaultMapTable[InputType::prev] = { {InputCategory::keybd,PAD_INPUT_7} };
				
	// タイトルへ
	defaultMapTable[InputType::title] = { {InputCategory::keybd,KEY_INPUT_RETURN} };

	// ポーズ
	defaultMapTable[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_8} };
										

	inputMapTable = defaultMapTable;

	// 一時マップテーブルにコピー
	tempMapTable = inputMapTable;
	
	currentInput.resize(static_cast<int>(InputType::max));
	lastInput.resize(static_cast<int>(InputType::max));
}

void InputState::Update()
{
	lastInput = currentInput;	// 直前の入力情報を記憶しておく
	
	char keystate[256];

	GetHitKeyStateAll(keystate);	// 全キー情報取得

	
	for (const auto& keymap : inputMapTable)
	{
		for (const auto& input : keymap.second)
		{
			// 入力情報配列をループする。このInputの中身は、keybd,KEY_INPUT_RETURNなどの
			// セット(InputInfo)が入っている。keymap.firstには、対応するゲーム入力名の
			// "InputType::next"などが入っている。

			if (input.cat == InputCategory::keybd)
			{
				currentInput[static_cast<int>(keymap.first)] = keystate[input.id];
			}

			// 入力のうちどれかがtrueだったらもう「入力されている」
			// とみなしてbreakする

			if (currentInput[static_cast<int>(keymap.first)])
			{
				break;
			}
		}

	}
}

void InputState::RewriteInputInfo(InputType type, InputCategory cat, int id)
{
	// 入力種別(割当先)がなければ無効なので無視
	if (tempMapTable.count(type) == 0)
	{
		return;
	}

	bool isRewrite = false;
	for (auto& InputInfo : tempMapTable[type])
	{
		if (InputInfo.cat == cat)
		{
			// カテゴリがヒットしたらIDを上書きする
			InputInfo.id = id;
			isRewrite = true;
			break;
		}
	}
	if (!isRewrite)
	{
		// もしカテゴリが存在しなかったら、ここで追加しておく
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

