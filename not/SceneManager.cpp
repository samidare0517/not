#include "SceneManager.h"
#include "Scene.h"

void SceneManager::CangeScene(Scene* scene)
{
	// Scene�X�^�b�N���󂶂�Ȃ�������
	if (!scenes_.empty())	// �Ӗ��Fempty = ���
	{
		delete scenes_.front();	// top�͂Ă��؂�̗v�f��Ԃ��Ă���
		scenes_.pop_front();	// 1���遨���ʂ�0�ɂȂ�
	}
	scenes_.push_front(scene);	// 1������
}

void SceneManager::PushScene(Scene* scene)
{
	scenes_.push_front(scene);	// 1������
}

void SceneManager::PopScene()
{
	// pop�̌��ʃV�[����0�ɂȂ�Ȃ��悤�ɂ���
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
