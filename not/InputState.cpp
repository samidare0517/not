#include "InputState.h"
#include "DxLib.h"
#include <cassert>

InputState::InputState()
{
	// 次へ
	defaultMapTable_[InputType::next] = { {InputCategory::keybd,KEY_INPUT_RETURN} };
									
	// 前へ
	defaultMapTable_[InputType::prev] = { {InputCategory::keybd,KEY_INPUT_SPACE} };
										
	// ポーズ
	defaultMapTable_[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_P} };
										

	inputMapTable_ = defaultMapTable_;

	// 一時マップテーブルにコピー
	tempMapTable_ = inputMapTable_;
	
	currentInput_.resize(static_cast<int>(InputType::max));
	lastInput_.resize(static_cast<int>(InputType::max));
}

void InputState::Update()
{
	lastInput_ = currentInput_;	// 直前の入力情報を記憶しておく
	
	char keystate[256];

	GetHitKeyStateAll(keystate);	// 全キー情報取得

	
	for (const auto& keymap : inputMapTable_)
	{
		for (const auto& input : keymap.second)
		{
			// 入力情報配列をループする。このInputの中身は、keybd,KEY_INPUT_RETURNなどの
			// セット(InputInfo)が入っている。keymap.firstには、対応するゲーム入力名の
			// "InputType::next"などが入っている。

			if (input.cat == InputCategory::keybd)
			{
				currentInput_[static_cast<int>(keymap.first)] = keystate[input.id];
			}

			// 入力のうちどれかがtrueだったらもう「入力されている」
			// とみなしてbreakする

			if (currentInput_[static_cast<int>(keymap.first)])
			{
				break;
			}
		}

	}
}

void InputState::RewriteInputInfo(InputType type, InputCategory cat, int id)
{
	// 入力種別(割当先)がなければ無効なので無視
	if (tempMapTable_.count(type) == 0)
	{
		return;
	}

	bool isRewrite = false;
	for (auto& InputInfo : tempMapTable_[type])
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
		tempMapTable_[type].push_back({ cat,id });
	}

}

bool InputState::IsTriggred(InputType type) const
{
	return currentInput_[static_cast<int>(type)];
}

bool InputState::IsPressed(InputType type) const
{
	return IsPressed(type) && !lastInput_[static_cast<int>(type)];
}

