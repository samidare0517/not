#pragma once

// #includeではなくプロトタイプ宣言
class SceneManager;	// シーンマネージャー
class InputState;	// 入力ステート

// なので、この時点ではSceneManagerとInputStateはポインタもしくは参照としてしか扱えない

/// <summary>
/// シーンの基底クラス
/// </summary>
class Scene
{
protected:	// 子クラスには見えるようにする
	SceneManager& manager_;	// シーンマネージャーへの参照

public:
	Scene(SceneManager& manager):manager_(manager){}
	virtual ~Scene() {};

	// シーンを更新する
	virtual void Update(const InputState& input) = 0;

	// シーンを描画する
	virtual void Draw() = 0;
};

