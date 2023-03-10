#include "SceneManager.h"
#include "Scene.h"

void SceneManager::End()	// �S�ẴV�[����delete������
{
	while (scenes.size() > 0)
	{
		delete scenes.front();
		scenes.pop_front();
	}
}

void SceneManager::CangeScene(Scene* scene)
{
	// Scene�X�^�b�N���󂶂�Ȃ�������
	if (!scenes.empty())	// �Ӗ��Fempty = ���
	{
		delete scenes.front();	// top�͂Ă��؂�̗v�f��Ԃ��Ă���
		scenes.pop_front();	// 1���遨���ʂ�0�ɂȂ�
	}
	scenes.push_front(scene);	// 1������
}

void SceneManager::PushScene(Scene* scene)
{
	scenes.push_front(scene);	// 1������
}

void SceneManager::PopScene()
{
	// pop�̌��ʃV�[����0�ɂȂ�Ȃ��悤�ɂ���
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
