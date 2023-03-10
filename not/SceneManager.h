#pragma once
#include <deque>

// �v���g�^�C�v�錾

class Scene;		// �V�[�����N���X
class InputState;	// ���̓X�e�[�g

// �V�[���Ď��N���X
class SceneManager
{
public:

	void End();

	/// <summary>
	/// �V�[���̐؂�ւ����s��
	/// </summary>
	/// <param name="scene">�؂�ւ��������̃V�[���̃A�h���X</param>
	void CangeScene(Scene* scene);

	/// <summary>
	/// �V�[���̏�ɐς�
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(Scene* scene);

	void PopScene();

	/// <summary>
	/// �e�V�[����Update(�X�V)���s��
	/// </summary>
	/// <param name="input">���̓X�e�[�g</param>
	void Update(const InputState& input);

	/// <summary>
	/// �e�V�[���̕`����s��
	/// </summary>
	void Draw();

private:
	// �u�����s���v�̃V�[����؂�ւ������̂ŎQ�Ƃł͂Ȃ��|�C���^�Ƃ��Đ錾
	std::deque<Scene*>scenes;

};

