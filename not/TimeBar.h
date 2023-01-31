#pragma once
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
	int tb;
	int handle;
	int frame;

};

