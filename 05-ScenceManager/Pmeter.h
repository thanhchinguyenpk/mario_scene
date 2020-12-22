#pragma once
#include "GameObject.h"
#include "Mario.h"

 //extern CMario* mario;

class Pmeter :public CGameObject
{
	
public:
	CMario* mario;
	int lv = 0;

	Pmeter(CMario* player);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	//virtual void SetState(int state);
	virtual void Render();
};

