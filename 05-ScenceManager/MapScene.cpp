#include "MapScene.h"
#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_CONCO	4
#define OBJECT_TYPE_PARA_GOOMBA 5

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

MapScene::MapScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new MapSceneKeyHandler(this);
}

void MapScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines
	//[texture] mà có 5 phần tử thì hàng đó sai 
	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);// file text của mình là aski thì nó là singlebyte charactor trong
	//khi project của mình sài unicode, cho nên viết hàm chuyển đổi chuỗi, chuyển đổi nó qua đường dẫn
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void MapScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void MapScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void MapScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void MapScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y
	/* ví dụ mario 0(loại object) 50(x) 0(y) 1(ani_set_id)*/
	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(); //CMario(x,y);
		obj->SetPosition(x, y);//khong có dong duoi
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		obj = new CGoomba(player);
		obj->SetState(GOOMBA_STATE_WALKING);
		break;
	}
	case OBJECT_TYPE_PARA_GOOMBA:
	{
		obj = new ParaGoomba(player);
		obj->SetState(PARA_GROOMBA_STATE_JUMP_BIG);
		break;
	}

	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	case OBJECT_TYPE_CONCO:
		obj = new CConCo();
		obj->SetState(CONCO_STATE_WALKING_LEFT);
		break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());// nhảy tới cổng nào
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	case 6:
	{
		int width = atof(tokens[4].c_str());
		int height = atof(tokens[5].c_str());
		int is_portal = atof(tokens[6].c_str());
		obj = new Flatform(width, height, is_portal);
		break;
		//dynamic_cast<Flatform*>

	}
	case 7:
	{
		int lv = atof(tokens[4].c_str());
		obj = new VenusFireTrap(player, lv);
		obj->SetState(VENUS_STATE_GOING_UP);
		break;
	}
	case 8:
	{
		//int lv = atof(tokens[4].c_str());
		obj = new PiranhaPlant(player);
		obj->SetState(PIRANHA_PLANT_STATE_GOING_UP);
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	// nhớ thêm đoạn code animation set mà null chẳng hạn 0:32:38
	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void MapScene::Render()
{
	map->Draw();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void MapScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;// có khả năng là mình quay lại cảnh đó!
	/*đi qua cảnh mới thì mình unload cảnh cũ, sau đó mình load cảnh mới lên, nhưng sau này mình có thể
	qay lại đúng cảnh cũ, nếu khog gán bằng null khi qua cảnh mới có thể trỏ lại cảnh cũ, thầy cẩn
	thận nên gán thui, mặc dù xác suất rất thấp*/
	// thầy nói sương sương nên chắc không cần

	/* thế sao không unload mấy cái texture mình load lên? câu trả lời á là khi mà qua cảnh mới
	thì cái việc unload đó không phỉa của playsence quản lí,
	Đơn giản là trong texttures.cpp á (Ctexture::clear()) có nghĩ là qua cảnh mới thì unload toàn
	bộ các texture.( nhưng con một số texture của mario vẫn còn sd, tự code nhen(nên tổ chức bên
	trong lớp game*/

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}


void MapScene::Update(DWORD dt)
{
	
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	/*if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	if (player->is_on_the_ground == false)
		CGame::GetInstance()->SetCamPos(cx, 700);*/
	//CGame::GetInstance()->SetCamPos(0,0);
}

void MapScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	//for(int i=0;i<tokens.size();i++)
	DebugOut(L"[INFO]10 mapid loading scene resources from : %s \n", line);

	if (tokens.size() < 6) return;

	//idStage
	//mapFilePath
	//Row of Map
	//Column of Map
	//tilesetFilePath
	//Row of Tileset
	//Column of Tileset


	/*
		int id,
		LPCWSTR mapFilePath,
		int RowMap,
		int ColumnMap,
		LPCWSTR mapFileTexture,
		int RowTile,
		int ColumnTile,
		int TileFrameWidth,
		int TileFrameHeight*/
	/*DebugOut(L"[INFO]0 mapid loading scene resources from : %d \n", atoi(tokens[0].c_str()));
	DebugOut(L"[INFO]1 path pic scene resources from : %s \n", ToLPCWSTR(tokens[1]));
	DebugOut(L"[INFO]2 mapid loading scene resources from : %d \n", atoi(tokens[2].c_str()));
	DebugOut(L"[INFO]3 mapid loading scene resources from : %d \n", atoi(tokens[3].c_str()));
	DebugOut(L"[INFO]4 path pic scene resources from : %s \n", ToLPCWSTR(tokens[4]));
	*/
	map->LoadMap(atoi(tokens[0].c_str()),
		ToLPCWSTR(tokens[1]), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()),
		ToLPCWSTR(tokens[4]), atoi(tokens[5].c_str()), atoi(tokens[6].c_str()));

	//map->LoadMap(0, L"textures\\map_thanh.txt", 41, 176, L"textures\\Final1.png", 30, 29, 48, 48);

	//camMaxWidth = atoi(tokens[7].c_str());
}

void MapScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);
	map = new Map();

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines
		//thấy dấu rào là bỏ qua

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	// một là đang ở dòng data
		//hai là đang ở section không biết đó là gì , để tránh khi đôi lúc chế section mà quên if vô 
		//trong file này á .

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);

	
}

void MapSceneKeyHandler::KeyState(BYTE * states)
{
}

void MapSceneKeyHandler::OnKeyDown(int KeyCode)
{
}

void MapSceneKeyHandler::OnKeyUp(int KeyCode)
{
}
