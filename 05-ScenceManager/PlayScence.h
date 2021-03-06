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
#include "Coin.h"
#include "RandomBonus.h"
#include "Pine.h"
#include <vector>
#include "MovingFlatform.h"
#include "BoomerangBrother.h"
#include "BoomerangWeapon.h"
#include "BrickBlinkCoin.h"

#include "Grid.h"


#define ITEM_MONEY 0
#define ITEM_RANDOM 1


class CPlayScene: public CScene
{
public: 

	CGrid * grid;

	int card = 0;
	bool is_mario_got_card = false;
	CMario *player;					// A play scene has to have player, right? 

	int point_hub = 0;
	int the_number_mario_hit_brick = 0;


	UI* game_ui;
	GameTime* game_time;
	

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> itemsMarioCanEat;
	vector<LPGAMEOBJECT> listBricks;
	vector<LPGAMEOBJECT> ghost_platforms;//cd
	vector<LPGAMEOBJECT> enemies;//dr


	void DropItem(int itemType, float x, float y);

	Map* map;


	

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_OBJECTS_GRID(string line);

	void _ParseSection_MAP(string line);
	
	

	

	CPlayScene(int id, LPCWSTR filePath);

	virtual void LoadSceneResources();
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario * GetPlayer() { return player; } 

	

	void SetEnemiesInScene(vector<LPGAMEOBJECT> listEnemy) { enemies.clear(); enemies = listEnemy; }
	void SetItemsInScene(vector<LPGAMEOBJECT> listItem) { }
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {  };
};

