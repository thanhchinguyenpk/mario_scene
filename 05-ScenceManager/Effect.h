#pragma once
#include "GameObject.h"

class Effect : public CGameObject
{
protected:
	ULONGLONG startEffect;
	int effectTime=800;
public:
	Effect();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render() = 0;
	~Effect();
};