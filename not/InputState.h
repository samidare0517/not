#pragma once
#include<map>
#include<vector>
#include<string>

// �Q�[�����Ŏg�p����鉼�z���͏��
enum class InputType
{
	next,	// ���֍s���{�^��
	prev,	// �O�ɖ߂�{�^��
	title,	// �^�C�g���ɖ߂�
	pause,	// �|�[�Y�{�^��
	max		// �ő���̓C���f�b�N�X
};

/// <summary>
/// ���͑��u
/// </summary>
enum class InputCategory
{
	pad,	// �p�b�h
};

/// <summary>
/// ���͏��
/// </summary>
struct InputInfo
{
	InputCategory cat;	// ���͑��u�J�e�S��
	int id;				// ����ID(KEY_INPUT�`,PAD_INPUT_�`,MOUSE_INPUT_�`�@������)
};

/// <summary>
/// ���͏�Ԃ��Ǘ�����
/// </summary>
class InputState
{

public:

	InputState();

	/// <summary>
	/// �������u��true�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>�������u�ԂȂ�true�E����ȊO�Ȃ�false</returns>
	bool IsTriggred(InputType type)const;

	/// <summary>
	/// ������Ă�����true�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>������Ă�����true�E������ĂȂ��Ȃ�false</returns>
	bool IsPressed(InputType type)const;

	/// <summary>
	/// ���͏����X�V����
	/// (����)���t���[��Update���Ă΂Ȃ��Ɠ��͏�Ԃ͍X�V����Ȃ��B
	/// </summary>
	void Update();

	/// <summary>
	/// ���͏�Ԃ��X�V����
	/// </summary>
	/// <param name="type">�Q�[���ɂ�������͎��</param>
	/// <param name="cat">���̓J�e�S��</param>
	/// <param name="id">���ۂ̓���</param>
	void RewriteInputInfo(InputType type, InputCategory cat, int id);

private:

	// ���z���͏��ƁA���ۂ̓��̓e�[�u�������
	// �L�[(first) = InputType
	// �l(second) = std::vector<InputInfo.
	using InputMap_t = std::map<InputType, std::vector<InputInfo>>;

	// ���ۂ̓��͂ƑΉ��̃{�^��
	InputMap_t inputMapTable;

	// ���������p�̈ꎞ�I�Ȃ̃R�s�[
	// �����Ȃ菑�������Ă��܂�Ȃ��悤��
	InputMap_t tempMapTable;

	// ���Z�b�g�p�L�[�}�b�v�e�[�u��
	InputMap_t defaultMapTable;

	// ���̓^�C�v�Ƃ��̖��O�̃e�[�u��
	std::map < InputType, std::wstring> inputNameTable;

	std::vector<bool>currentInput;		// ���݂̓��͏��(�����Ă��邩�����Ă��Ȃ���)
	std::vector<bool>lastInput;		// ���O�̓��͏��(���O�����Ă��邩�����Ă��Ȃ���)

};

