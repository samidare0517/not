#pragma once

/// <summary>
/// �~�b�N�X�p�^�C���o�[
/// </summary>

class MixTimeBar
{
public:

	MixTimeBar();
	~MixTimeBar();

	void Init();
	void Update();
	void Draw();

	bool Check();

private:

	// �^�C���o�[
	int mtb = 0;

	// �摜�n���h��
	int handle = 0;

	// �^�C���o�[�p�̔w�i�n���h��
	int mixTimeBackHandle = 0;

	// �t���[��
	int frame = 0;

	// �\���p�^�C�}�[
	int time = 4;

};

