#pragma once
#include "Game.h"

#define ONE_SECOND_UNIT			1000

class GameTime
{
	static GameTime* __instance;
	DWORD currentTotalTime;
	int gameTime;
	bool isStop;
	

	GameTime();
	~GameTime();

public:
	static GameTime* GetInstance();
	void Update(DWORD dt);
	void SetTime(int time) { gameTime = time; }
	int GetTime() { return gameTime; }
	void ResetGameTime() { gameTime = 0; }
	void SetTimeStop(bool b) { isStop = b; }

	



};

