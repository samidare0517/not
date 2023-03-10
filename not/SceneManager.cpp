#include "SceneManager.h"
#include "Scene.h"

void SceneManager::End()	// 全てのシーンのdeleteをする
{
	while (scenes.size() > 0)
	{
		delete scenes.front();
		scenes.pop_front();
	}
}

void SceneManager::CangeScene(Scene* scene)
{
	// Sceneスタックが空じゃなかったら
	if (!scenes.empty())	// 意味：empty = 空の
	{
		delete scenes.front();	// topはてっぺんの要素を返している
		scenes.pop_front();	// 1個減る→普通は0になる
	}
	scenes.push_front(scene);	// 1個増える
}

void SceneManager::PushScene(Scene* scene)
{
	scenes.push_front(scene);	// 1個増える
}

void SceneManager::PopScene()
{
	// popの結果シーンが0にならないようにする
	if (scenes.size() > 1)
	{
		delete scenes.front();
		scenes.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	scenes.front()->Update(input);
}

void SceneManager::Draw()
{
	for (int i = scenes.size() - 1; i >= 0; --i)
	{
		scenes[i]->Draw();
	}
}
