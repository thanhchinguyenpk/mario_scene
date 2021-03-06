﻿#pragma once
#include "Scence.h"
#include "Mario.h"
#include "Map.h"
#include "CMapPortal.h"
#include "InvisibleObject.h"
#include "GameTime.h"
#include "UI.h"



class MapScene : public CScene
{
public:

	

	CMario* player;
	vector<LPGAMEOBJECT> objects;
	Map* map;
	MapScene(int id, LPCWSTR filePath);

	CMapPortal* current_portal;
	vector<LPGAMEOBJECT> map_portals;
	vector<LPGAMEOBJECT> ghost_platforms;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_STATIC_OBJECTS(string line);

	void _ParseSection_MAP_SELECTION(string line);//mấy cái cổng 

	void _ParseSection_MAP(string line);

	UI* game_ui;
	GameTime* game_time;

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; };

	void SetEnemiesInScene(vector<LPGAMEOBJECT> listEnemy) { objects.clear(); objects = listEnemy; }

};

class MapSceneKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	MapSceneKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};
