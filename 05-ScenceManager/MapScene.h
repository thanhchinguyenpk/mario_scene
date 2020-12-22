#pragma once
#include "Scence.h"
#include "Mario.h"
#include "Map.h"

class MapScene : public CScene
{
public:
	CMario* player;
	vector<LPGAMEOBJECT> objects;
	Map* map;
	MapScene(int id, LPCWSTR filePath);

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP(string line);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

};

class MapSceneKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	MapSceneKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};
