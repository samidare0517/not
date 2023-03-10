#pragma once
#include <deque>

// プロトタイプ宣言

class Scene;		// シーン基底クラス
class InputState;	// 入力ステート

// シーン監視クラス
class SceneManager
{
public:

	void End();

	/// <summary>
	/// シーンの切り替えを行う
	/// </summary>
	/// <param name="scene">切り替えたい次のシーンのアドレス</param>
	void CangeScene(Scene* scene);

	/// <summary>
	/// シーンの上に積む
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(Scene* scene);

	void PopScene();

	/// <summary>
	/// 各シーンのUpdate(更新)を行う
	/// </summary>
	/// <param name="input">入力ステート</param>
	void Update(const InputState& input);

	/// <summary>
	/// 各シーンの描画を行う
	/// </summary>
	void Draw();

private:
	// 「今実行中」のシーンを切り替えたいので参照ではなくポインタとして宣言
	std::deque<Scene*>scenes;

};

