#pragma once
#include "Scene.h"
#include <memory>

class Field;
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

	// �t���[��
	int frame = 0;

	// �\���p�̃^�C�}�[(3�b)
	int time = 3;

};
