#include "Effect.h"

Effect::Effect()
{
	
	startEffect = GetTickCount64();
}

void Effect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount64() - startEffect > effectTime)
		used = true;
}

Effect::~Effect()
{
}
