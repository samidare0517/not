#include "SceneManager.h"
#include "Scene.h"

void SceneManager::CangeScene(Scene* scene)
{
	// Sceneスタックが空じゃなかったら
	if (!scenes_.empty())	// 意味：empty = 空の
	{
		delete scenes_.front();	// topはてっぺんの要素を返している
		scenes_.pop_front();	// 1個減る→普通は0になる
	}
	scenes_.push_front(scene);	// 1個増える
}

void SceneManager::PushScene(Scene* scene)
{
	scenes_.push_front(scene);	// 1個増える
}

void SceneManager::PopScene()
{
	// popの結果シーンが0にならないようにする
	if (scenes_.size() > 1)
	{
		delete scenes_.front();
		scenes_.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	scenes_.front()->Update(input);
}

void SceneManager::Draw()
{
	for (int i = scenes_.size() - 1; i >= 0; --i)
	{
		scenes_[i]->Draw();
	}
}
