#include "GameTime.h"


GameTime* GameTime::__instance = NULL;


void GameTime::Update(DWORD dt)
{
	if (!isStop)
	{
		//Cu 1000ms thi +gametime len 1 lan
		if (currentTotalTime + dt > ONE_SECOND_UNIT)
		{
			//Lay phan thua` cua dt ra
			currentTotalTime = (currentTotalTime + dt) % ONE_SECOND_UNIT;
			gameTime++;
		}
		else
			currentTotalTime += dt;
	}
}

GameTime* GameTime::GetInstance()
{
	if (__instance == NULL) __instance = new GameTime();
	return __instance;
}

GameTime::GameTime()
{
	currentTotalTime = 0;
	gameTime = 0;
	isStop = false;
}

GameTime::~GameTime()
{
}
