#pragma once
#include "Scene.h"
#include <memory>

class KeyField;
class PadField;
/// <summary>
/// �^�C���o�[
/// </summary>
class TimeBar
{
public:

	TimeBar();
	~TimeBar();

	void Init();
	void Update();
	void Draw();

	bool Check();
	
private:

	// �^�C���o�[
	int tb = 0;

	// �摜�n���h��
	int handle = 0;

	// �^�C���o�[�p�̔w�i�n���h��
	int timeBackHandle = 0;

	// �^�C�}�[�p�̉摜�n���h��
	int timerBackHandle = 0;

	// �t���[��
	int frame = 0;

	// �\���p�^�C�}�[
	int time = 3;

};
