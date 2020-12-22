#pragma once
#include "GameObject.h"
#include "Pmeter.h"
#include "Mario.h"

class Hub :public CGameObject
{
public:
	CMario * mario;
	Pmeter* pmeter;
	Hub(CMario* player);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
};

