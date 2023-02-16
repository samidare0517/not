#pragma once
#include<map>
#include<vector>
#include<string>

// ゲーム中で使用される仮想入力情報
enum class InputType
{
	next,	// 次へ行くボタン
	prev,	// 前に戻るボタン
	title,	// タイトルに戻る
	pause,	// ポーズボタン
	max		// 最大入力インデックス
};

/// <summary>
/// 入力装置
/// </summary>
enum class InputCategory
{
	pad,	// パッド
};

/// <summary>
/// 入力情報
/// </summary>
struct InputInfo
{
	InputCategory cat;	// 入力装置カテゴリ
	int id;				// 入力ID(KEY_INPUT～,PAD_INPUT_～,MOUSE_INPUT_～　が入る)
};

/// <summary>
/// 入力状態を管理する
/// </summary>
class InputState
{

public:

	InputState();

	/// <summary>
	/// 押した瞬間trueになる
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>押した瞬間ならtrue・それ以外ならfalse</returns>
	bool IsTriggred(InputType type)const;

	/// <summary>
	/// 押されていたらtrueになる
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>押されていたらtrue・押されてないならfalse</returns>
	bool IsPressed(InputType type)const;

	/// <summary>
	/// 入力情報を更新する
	/// (注意)毎フレームUpdateを呼ばないと入力状態は更新されない。
	/// </summary>
	void Update();

	/// <summary>
	/// 入力状態を更新する
	/// </summary>
	/// <param name="type">ゲームにおける入力種別</param>
	/// <param name="cat">入力カテゴリ</param>
	/// <param name="id">実際の入力</param>
	void RewriteInputInfo(InputType type, InputCategory cat, int id);

private:

	// 仮想入力情報と、実際の入力テーブルを作る
	// キー(first) = InputType
	// 値(second) = std::vector<InputInfo.
	using InputMap_t = std::map<InputType, std::vector<InputInfo>>;

	// 実際の入力と対応のボタン
	InputMap_t inputMapTable;

	// 書き換え用の一時的なのコピー
	// いきなり書き換えてしまわないように
	InputMap_t tempMapTable;

	// リセット用キーマップテーブル
	InputMap_t defaultMapTable;

	// 入力タイプとその名前のテーブル
	std::map < InputType, std::wstring> inputNameTable;

	std::vector<bool>currentInput;		// 現在の入力情報(押しているか押していないか)
	std::vector<bool>lastInput;		// 直前の入力情報(直前押しているか押していないか)

};

