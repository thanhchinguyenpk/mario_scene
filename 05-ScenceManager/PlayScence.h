#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "ConCo.h"
#include "ParaGoomba.h"
#include "Flatform.h"
#include "MarioBullet.h"
#include "VenusFireTrap.h"
#include "PiranhaPlant.h"
#include "Hub.h"
#include "UI.h"
#include "GameTime.h"
#include "Brick_Coin.h"
#include "BrickBlink.h"
#include "Mushroom.h"
#include "SuperLeaf.h"
#include "CoinEffect.h"

#define ITEM_RANDOM 0
#define ITEM_MONEY 1

class CPlayScene: public CScene
{
public: 

	CMario *player;					// A play scene has to have player, right? 

	UI* game_ui;
	GameTime* game_time;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> itemsMarioCanEat;
	void DropItem(int itemType, float x, float y);

	Map* map;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP(string line);
	
	

	

	CPlayScene(int id, LPCWSTR filePath);

	virtual void LoadSceneResources();
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {  };
};

