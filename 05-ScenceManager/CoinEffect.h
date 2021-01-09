#pragma once
#include "GameObject.h"
#include "Effect.h"
#include "MoneyEffect.h"

class CoinEffect :public Effect
{
public:
	bool make_sure_go_down = false;
	bool vanish = false;
	float minPosY; //theo thu tu xa gan
	float maxPosY;
	MoneyEffect* effect=NULL;

	CoinEffect(float brickX, float brickY);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

