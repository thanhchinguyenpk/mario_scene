#pragma once
#include "Effect.h"
class MoneyEffect : public Effect
{
public:

	MoneyEffect(int pos_x,int pos_y, int moneyAni = 0);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	~MoneyEffect();


};

