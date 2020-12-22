#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"

class CMapPortal : public CGameObject
{
public:
	int id_portal;

	int is_portal;
	int t, l, r, b;
				//int id, float x, float y, int state, bool is_portal, int l, int t, int r, int b
	
	CMapPortal(int id, float x, float y, bool is_portal, int t, int r, int b, int l, int state);
	~CMapPortal() {};

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
};

