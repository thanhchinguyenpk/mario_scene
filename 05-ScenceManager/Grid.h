#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Mario.h"
/*
#include "Textures.h"
#include "Scence.h"

#include "Brick.h"

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
*/

//173 186.25
#define CELL_HEIGHT (692/4.0f)
#define CELL_WIDTH (745/4.0f)

// 12 48
//#define MAX_ROW (int)(SCENE_HEIGHT/CELL_HEIGHT) + 1
//#define MAX_COLUMN (int)(SCENE_WIDTH/CELL_WIDTH) + 1
#define MAX_ROW 13
#define MAX_COLUMN 47


class CGrid
{
public:

	CMario *player = NULL;

	vector<LPGAMEOBJECT> total_obj;
	vector<LPGAMEOBJECT> enemies;

	vector<LPGAMEOBJECT> cells[MAX_ROW][MAX_COLUMN];


	LPCWSTR objFilePath;
	LPCWSTR gridFilePath;

	void Classify(LPGAMEOBJECT obj);
	void GetListObjInGrid(float cam_x, float cam_y);

	void UpdatePositionInGrid(float cam_x, float cam_y);

	LPGAMEOBJECT CreateNewObj(int obj_type, float x, float y, float w, float h, int ani_id, int type, int extra = 0, int nx = 1, int angle = 1, int id_grid = 0);

	void ReadFileObj();
	void ReadFileGrid();


	CGrid(LPCWSTR objFilePath, LPCWSTR gridFilePath,CMario *mario);
	~CGrid() {};


};

