#pragma once
#include <memory>

class Field;

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
	int tb = 0;
	int handle = 0;
	int frame = 0;

};
