#pragma once
#include <Windows.h>
class TimerCustom
{
public:
	int startTime;
	int limitTime;
	
public:

	TimerCustom(int limitTime) { this->limitTime = limitTime; startTime = 0;};

	TimerCustom() {};
	~TimerCustom() {};


	void StartTime() { startTime = GetTickCount64(); };
	bool IsTimeUp() { return (startTime && GetTickCount64() - startTime >= limitTime); };
	void Reset() { startTime = 0; }
};

