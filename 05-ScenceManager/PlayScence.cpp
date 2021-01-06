#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "ConCo.h"
#include "Pmeter.h"


using namespace std;

//Ngay khi lơp playScene được tạo ra thì mình tạo ra moojt cái key_handler mới để mình xử lí bàn phím
CAnimationSets * animation_sets = CAnimationSets::GetInstance();

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);

	//suy nghĩ hướng khác 0:35:38
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

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


void CPlayScene::DropItem(int itemType, float x, float y)
{
	switch (itemType)
	{
	case ITEM_RANDOM:
	{
		if (player->GetLevel() == MARIO_LEVEL_SMALL)
		{
			Mushroom* mushroom = new Mushroom(x, y);
			itemsMarioCanEat.push_back(mushroom);
		}
		else if (player->GetLevel() == MARIO_LEVEL_BIG)
		{
			SuperLeaf *superleaf = new SuperLeaf(x, y);
			itemsMarioCanEat.push_back(superleaf);
		}
		break;
	}
	case ITEM_MONEY:
	{
		CoinEffect* coineffect = new CoinEffect(x, y);
		itemsMarioCanEat.push_back(coineffect);
		break;
	}

	}
}


	void CPlayScene::_ParseSection_TEXTURES(string line)
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

void CPlayScene::_ParseSection_SPRITES(string line)
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

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
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

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
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
		if (player!=NULL) 
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
		obj->SetState(CONCO_STATE_FLY_RIGHT);
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
		obj->SetState(CONCO_STATE_FLY_LEFT);
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
		int width= atof(tokens[4].c_str());
		int height = atof(tokens[5].c_str());
		int is_portal = atof(tokens[6].c_str());
		obj = new Flatform(width, height, is_portal);
		break;
		//dynamic_cast<Flatform*>
		
	}
	case 7:
	{
		int lv= atof(tokens[4].c_str());
		obj = new VenusFireTrap(player,lv);
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
	case 9:
	{
		//int lv = atof(tokens[4].c_str());
		obj = new Hub(player);
		//obj->SetState(PIRANHA_PLANT_STATE_GOING_UP);
		break;
	}
	case 10:
	{
		//int lv = atof(tokens[4].c_str());
		obj = new Brick_Coin(y);
		obj->SetState(BRICK_COIN_STATE_CHUA_DAP);
		break;
	}
	case 11:
	{
		//int lv = atof(tokens[4].c_str());
		obj = new BrickBlink(player);
		//obj->SetState(BRICK_COIN_STATE_CHUA_DAP);
		break;
	}
	case 12:
	{
		//int lv = atof(tokens[4].c_str());
		obj = new Coin();
		//obj->SetState(BRICK_COIN_STATE_CHUA_DAP);
		break;
	}
	case 13:
	{
		//int lv = atof(tokens[4].c_str());
		obj = new RandomBonus(player);
		//obj->SetState(BRICK_COIN_STATE_CHUA_DAP);
		break;
	}
	case 14:
	{
		int state = atof(tokens[4].c_str());
		obj = new Pine();
		obj->SetState(state);
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

	if(dynamic_cast<BrickBlink*>(obj))
	{
		listBricks.push_back(obj);
		DebugOut(L"[ERR]mấy viên? object type: %d\n", object_type);
	} else if (dynamic_cast<RandomBonus*>(obj))
		itemsMarioCanEat.push_back(obj);
	else
		objects.push_back(obj);


	
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	//for(int i=0;i<tokens.size();i++)
		DebugOut(L"[INFO]10 mapid loading scene resources from : %s \n",line );

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
	DebugOut(L"[INFO]0 mapid loading scene resources from : %d \n", atoi(tokens[0].c_str()));
	DebugOut(L"[INFO]1 path pic scene resources from : %s \n", ToLPCWSTR(tokens[1]));
	DebugOut(L"[INFO]2 mapid loading scene resources from : %d \n", atoi(tokens[2].c_str()));
	DebugOut(L"[INFO]3 mapid loading scene resources from : %d \n", atoi(tokens[3].c_str()));
	DebugOut(L"[INFO]4 path pic scene resources from : %s \n", ToLPCWSTR(tokens[4]));

	map->LoadMap(atoi(tokens[0].c_str()),
		ToLPCWSTR(tokens[1]), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()),
		ToLPCWSTR(tokens[4]), atoi(tokens[5].c_str()), atoi(tokens[6].c_str()));

	//map->LoadMap(0, L"textures\\map_thanh.txt", 41, 176, L"textures\\Final1.png", 30, 29, 48, 48);

	//camMaxWidth = atoi(tokens[7].c_str());
}

void CPlayScene::LoadSceneResources()
{
}

void CPlayScene::Load()
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
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
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

	game_ui = new UI();
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	
	GameTime::GetInstance()->Update(dt);

	vector<LPGAMEOBJECT> coObjects;



	for (size_t i = 1; i < objects.size(); i++)
		coObjects.push_back(objects[i]);

	for (size_t i = 0; i < listBricks.size(); i++)
		coObjects.push_back(listBricks[i]);




	for (size_t i = 0; i < itemsMarioCanEat.size(); i++)
	{
		itemsMarioCanEat[i]->Update(dt, &coObjects);
	}

	for (size_t i = 0; i < listBricks.size(); i++)
	{
		listBricks[i]->Update(dt, &coObjects);
	}

	


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);

		//LPGAMEOBJECT e = objects[i];
		if (dynamic_cast<Brick_Coin*>(objects[i]))
		{
			Brick_Coin*brick = dynamic_cast<Brick_Coin*>(objects[i]);
			if (brick->is_hit == true && brick->dropped == false)
			{
				DropItem(1, brick->x, brick->y);
				brick->dropped = true;

				this->the_number_mario_hit_brick++;
				this->point_hub += 100;

				//DebugOut(L"[ERROR------------vo tao mushroom khong a--------------] DINPUT::GetDeviceData failed. Error: \n");
			}
		}
	}


	/*for (auto& item : listBricks)
	{
		if (item->used == true)
		{
			//if (dynamic_cast<SuperLeaf*>(pointer))
			//	DebugOut(L"xoas roi ne!\n");
				
			delete item;
			item = nullptr;
			DebugOut(L"xoas roi ne!\n");
			
		}
	}
	*/
	for (size_t i = 0; i < listBricks.size(); i++)
	{
		if (listBricks[i]->used==true)
		{
			delete listBricks[i];
			listBricks[i] = nullptr;

			listBricks.erase(listBricks.begin() + i);
		}
		
	}


	//listBricks.erase(std::remove(listBricks.begin(), listBricks.end(), nullptr), listBricks.end());


	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	cx += 200;

	if (cx < 0)
		return;
	if (cx > 8447 - SCREEN_WIDTH + MARIO_BIG_BBOX_WIDTH / 2)
		return;

	if (player->is_on_the_ground == false)
		CGame::GetInstance()->SetCamPos(cx, 700);
	else
		//	CGame::GetInstance()->SetCamPos(2064 * 3 + 16 * 3, 456 * 3);
	{
		if (cx > 7251 - SCREEN_WIDTH + MARIO_BIG_BBOX_WIDTH / 2)//7251 là cạnh phải của hộp hình chữ nhật camera
			return;
		CGame::GetInstance()->SetCamPos(cx, 1368);
	}
}

void CPlayScene::Render()
{
	map->Draw();
	
	for (int i = 0; i < listBricks.size(); i++)
		listBricks[i]->Render();
	

	for (int i = 0; i < itemsMarioCanEat.size(); i++)
		itemsMarioCanEat[i]->Render();

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	game_time = GameTime::GetInstance();
	game_ui->Render(300 - game_time->GetTime(), the_number_mario_hit_brick, point_hub,4,1);

	if(is_mario_got_card)
	{
		float x = CGame::GetInstance()->GetCamX();
		float y = CGame::GetInstance()->GetCamY();

		CSprites::GetInstance()->Get(40040 + card)->DrawFlipX(x + 534, y + 645, 0, 255, 1, 1);
	}
			
	
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
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

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	//vector<LPGAMEOBJECT> objects = ((CPlayScene*)scence)->objects;

	switch (KeyCode)
	{

	case DIK_K:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX() + 100, CGame::GetInstance()->GetCamY());
		break;
	case DIK_U:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() - 100);
		break;
	case DIK_G:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX() - 100, CGame::GetInstance()->GetCamY());
		break;
	case DIK_N:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() + 50);
		break;
		/*case DIK_5:
			goomba = new CGoomba();
			goomba->AddAnimation(701);
			goomba->AddAnimation(702);
			goomba->AddAnimation(703);
			goomba->SetPosition(mario->x+500, 100);
			goomba->SetState(GOOMBA_STATE_WALKING);
			objects.push_back(goomba);
			break;
		case DIK_6:
			conco = new CConCo();
			conco->AddAnimation(901);
			conco->AddAnimation(902);
			conco->AddAnimation(903);
			conco->AddAnimation(904);
			conco->AddAnimation(905);
			conco->AddAnimation(906);
			conco->AddAnimation(907);
			conco->AddAnimation(908);
			conco->SetPosition(mario->x + 500, 100.0f);
			conco->SetState(CONCO_STATE_WALKING_LEFT);//CONCO_STATE_WALKING_LEFT
			objects.push_back(conco);
				break;*/
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPosition(mario->x, mario->y-30);
		//goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);
		break;
	case DIK_2:
		mario->SetPosition(mario->x, mario->y - 30);
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_3:
		mario->SetPosition(mario->x, mario->y - 30);
		mario->SetLevel(MARIO_LEVEL_BIG_TAIL);
		break;
	case DIK_4:
		mario->SetPosition(mario->x, mario->y - 30);
		mario->SetLevel(MARIO_LEVEL_BIG_ORANGE);
		break;
	case DIK_5:
		
		break;
	case DIK_6:
		
		break;
	case DIK_7:
		
		break;
	case DIK_8:
	
		break;
	case DIK_9:
		
		break;
	case DIK_0:
		
		break;
	case DIK_R:
		mario->SetState(MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT);
		break;
	case DIK_H:
		mario->is_press_h = true;
		break;
	case DIK_Q:
		//mario->SetPosition(mario->GetX()+5, mario->GetY());
		//mario->SetState(MARIO_STATE_JUMP);
	//	if (mario->GetIsInObject() == false)
	//	{
		if (mario->is_run_for_fly_high)
		{
			mario->SetIsInObject(false);
			mario->SetState(MARIO_STATE_FLY_HIGH);
			mario->SetIsFly(true);
		}

		//	}
		break;
	case DIK_LEFT:
		mario->is_press_left = true;
		break;
	case DIK_S:
		//case 14:
		float x, y;
		mario->GetPosition(x, y);
		if (x > 6966 && mario->is_on_the_ground)
		{
			mario->is_go_down_pine = true;
			mario->SetPosition(x, y - 40);
			mario->SetState(MARIO_STATE_GO_UP_PINE);

			mario->go_down_pine_then_move_cam = GetTickCount64();
		}else if (mario->GetIsInObject() == true && mario->is_run_for_fly_high == false)
		{
			mario->StartJumping();
			mario->SetState(MARIO_STATE_JUMP);
			mario->SetIsInObject(false);
		}
		else
		{
			if (mario->is_run_for_fly_high == true)
			{
				mario->SetIsInObject(false);
				mario->SetState(MARIO_STATE_FLY_HIGH);
				mario->SetIsFly(true);
			}
			else if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			{
				mario->SetState(MARIO_STATE_FLY);
				mario->SetIsFly(true);
			}
		}
		//DebugOut(L"[INFO] KeyAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADown: %d\n", KeyCode);

		break;
	case DIK_A:
	case DIK_BACKSPACE:
		//case DIK_BACKSPACE:// reset
		/*mario->SetState(MARIO_STATE_IDLE);
			mario->SetLevel(MARIO_LEVEL_BIG);
			mario->SetPosition(50.0f,0.0f);
			mario->SetSpeed(0, 0);*/
		mario->is_press_h = true; // cho trạng thái cấm mai rùa

		DebugOut(L"[INFO] ssssssssssssssssssssssssssssssssssssssssssssss: %d\n", KeyCode);

		if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
		{

			mario->SetSpin(true);
			mario->SetState(MARIO_STATE_SPIN);

		}
		else if (mario->GetLevel() == MARIO_LEVEL_BIG_ORANGE)
		{
			if (mario->GetIsInObject() == true)
				mario->SetState(MARIO_STATE_SHOOT_BULLET);
			else
				mario->SetState(MARIO_STATE_JUMP_SHOOT_BULLET);

			mario->Attack();
			/*CGameObject * temp = new MarioBullet();


			//LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
			// nhớ thêm đoạn code animation set mà null chẳng hạn 0:32:38
			//obj->SetAnimationSet(ani_set);

			LPANIMATION_SET ani_set = animation_sets->Get(4);
			temp->SetAnimationSet(ani_set);
			//temp->AddAnimation(14002);

			if (mario->GetNX() > 0)
			{
				temp->SetState(MARIOBULLET_STATE_WALKING_RIGHT);
				temp->SetPosition(mario->GetX() + 10 + 5, mario->GetY());
			}
			else
			{
				temp->SetState(MARIOBULLET_STATE_WALKING_LEFT);
				temp->SetPosition(mario->GetX() - 5, mario->GetY());
			}
			

			//objects.push_back(temp);
			((CPlayScene*)scence)->objects = objects;*/
			mario->SetShoot(true);

		}



		break;
	case DIK_DOWN:
	
		//float x, y;
		mario->GetPosition(x, y);
		if (x < 600)
		{
			mario->is_go_down_pine = true;
			mario->go_down_pine_then_move_cam = GetTickCount64();
			mario->SetState(MARIO_STATE_GO_DOWN_PINE);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_BIG || mario->GetLevel() == MARIO_LEVEL_BIG_ORANGE)
			mario->SetPosition(mario->x, mario->y + MARIO_BIG_BBOX_HEIGHT / 2 - MARIO_BIG_SITDOWN_BBOX_HEIGHT / 2);
		else if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			mario->SetPosition(mario->x, mario->y + MARIO_BIG_TAIL_BBOX_HEIGHT / 2 - MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT / 2);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();

	switch (KeyCode)
	{
	case DIK_S:
		mario->EndJumping();
		//DebugOut(L"[INFO] KeyAAAAAAAAAAAAABBBBBBBBBBBBBBBAAAAAAAAAAAAADown: %d\n", KeyCode);
		break;
	case DIK_Q:
		mario->SetIsBring(false);
		break;
		//case DIK_BACKSPACE:
			//mario->SetShoot(false);
			//mario->SetSpin(false);
	case DIK_H:

		if (mario->hold_somthing != NULL)
		{
			mario->is_press_h = false;
			CConCo* conco = dynamic_cast<CConCo*>(mario->hold_somthing);
			conco->is_brought = false;
			conco->is_brought = false;
			conco->SetState(CONCO_STATE_MAI_RUA_CHAY_TRAI);
			mario->hold_somthing = NULL;
			mario->is_bring = false;
			mario->SetState(MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT);
		}

		break;
	case DIK_RIGHT:

		break;
	case DIK_LEFT:
		mario->is_press_left = false;
		break;

	case DIK_DOWN:
		//DebugOut(L"UPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPp\n", KeyCode);

		/*if (mario->is_in_portal == true);
		{
			if (mario->GetLevel() == MARIO_LEVEL_BIG || mario->GetLevel() == MARIO_LEVEL_BIG_ORANGE)
			mario->SetPosition(mario->x, mario->y - MARIO_BIG_BBOX_HEIGHT / 2 + MARIO_BIG_SITDOWN_BBOX_HEIGHT / 2);
		else if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			mario->SetPosition(mario->x, mario->y - MARIO_BIG_TAIL_BBOX_HEIGHT / 2 + MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT / 2);

		}*/
		break;

	case DIK_A:
		mario->SetIsIncreaseSpeed(false);
		mario->is_press_z = false;
		mario->is_run_for_fly_high = false;



		if (mario->hold_somthing != NULL) {
			mario->is_press_h = false;
			CConCo* conco = dynamic_cast<CConCo*>(mario->hold_somthing);
			conco->is_brought = false;

			if (mario->x < conco->x)
				conco->SetState(CONCO_STATE_MAI_RUA_CHAY_PHAI);
			else
				conco->SetState(CONCO_STATE_MAI_RUA_CHAY_TRAI);

			mario->hold_somthing = NULL;
			mario->is_bring = false;
			mario->SetState(MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT);
		}

		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	/*if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else
		mario->SetState(MARIO_STATE_IDLE);*/




		// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;

	if (game->IsKeyDown(DIK_A) && (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT)))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->is_press_z = true;
			mario->SetState(MARIO_STATE_WALKING_RIGHT);

			if (game->IsKeyDown(DIK_LEFT))
			{
				mario->nx = -1;
				mario->is_left = true;
				if (mario->is_right == false)
				{
					mario->SetAcceleration(-MARIO_ACCELERATION);
				}
				else
				{
					mario->SetAcceleration(-1.8 * MARIO_ACCELERATION);
					mario->is_slightly_lower_limit = true;
					mario->is_skid = true;
					if (mario->vx < 0) //tắt điều điện bên phải if dể sang chiều âm không vị vượt limit
					{
						mario->is_slightly_lower_limit = false;
						mario->is_skid = false;
					}
				}
			}

			if (game->IsKeyDown(DIK_RIGHT))
			{
				mario->nx = 1;
				mario->is_right = true;
				if (mario->is_left == false)
				{
					mario->SetAcceleration(MARIO_ACCELERATION);
				}
				else
				{
					mario->SetAcceleration(1.8 * MARIO_ACCELERATION);
					mario->is_slightly_lower_limit = true;
					mario->is_skid = true;

					//vận tốc lúc này đang là dương chuyển về âm rồi chuyển về dương
					if (mario->vx > 0)
					{
						mario->is_slightly_lower_limit = false;
						mario->is_skid = false;
					}
				}
			}


		}// huhu hai dòng dưới quan trọng
		//else
		//	mario->SetState(MARIO_STATE_WALKING_RIGHT);
		return;
	}
	/*else if (game->IsKeyDown(DIK_A))
	{
		float speed_x = abs(mario->vx);
		DebugOut(L"co vo diz z? \n");
		mario->is_press_z = true;
		if(speed_x > 0.4)
		{

			if (mario->nx > 0)
			{
				DebugOut(L"vo peed_x > 0.4 khong mario->nx > 0 \n");
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(-1.8 * MARIO_ACCELERATION);

			}
			else if (mario->nx < 0)
			{
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(1.8 * MARIO_ACCELERATION);
				DebugOut(L"vo tru bu luon moi ge \n");
			}

		}
		else
		{
			//mario->SetState(MARIO_STATE_IDLE); // co bug thi xem lai cho nay
			//mario->vx = 0;
			mario->is_slightly_lower_limit = false;
		}
		return;
	}*/



	if (game->IsKeyDown(DIK_RIGHT))
	{
		//mario->vx = MARIO_WALKING_SPEED;
		//mario->nx = 1;


		/*mario->SetAcceleration(MARIO_ACCELERATION);
		mario->SetState(MARIO_STATE_WALKING_RIGHT);*/
		//return;
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
		if (game->IsKeyDown(DIK_RIGHT))
		{
			mario->nx = 1;
			mario->is_right = true;
			if (mario->is_left == false)
			{
				mario->SetAcceleration(MARIO_ACCELERATION);
			}
			else
			{
				mario->SetAcceleration(1.2 * MARIO_ACCELERATION);
				mario->is_slightly_lower_limit = true;
				mario->is_skid = true;

				//vận tốc lúc này đang là dương chuyển về âm rồi chuyển về dương
				if (mario->vx > 0)
				{
					mario->is_slightly_lower_limit = false;
					mario->is_skid = false;
				}
			}
		}
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		//mario->vx = -MARIO_WALKING_SPEED;
		//mario->nx = -1;
		/*mario->SetAcceleration(-MARIO_ACCELERATION);
		mario->SetState(MARIO_STATE_WALKING_LEFT);*/
		//return;
		mario->SetState(MARIO_STATE_WALKING_LEFT);
		if (game->IsKeyDown(DIK_LEFT))
		{
			mario->nx = -1;
			mario->is_left = true;
			if (mario->is_right == false)
			{
				mario->SetAcceleration(-MARIO_ACCELERATION);
			}
			else
			{
				mario->SetAcceleration(-1.2 * MARIO_ACCELERATION);
				mario->is_slightly_lower_limit = true;
				mario->is_skid = true;
				if (mario->vx < 0) //tắt điều điện bên phải if dể sang chiều âm không vị vượt limit
				{
					mario->is_slightly_lower_limit = false;
					mario->is_skid = false;
				}
			}
		}
	}
	else if (game->IsKeyDown(DIK_DOWN))

		//	if (mario->is_in_portal == true)
		//	return;
		//if (mario->is_in_portal == fl)
		//if (mario->is_in_portal == true)

			//mario->SetState(MARIO_STATE_GO_DOWN_PINE);
	{
		if (mario->is_go_down_pine == false)
			mario->SetState(MARIO_STATE_SITDOWN);
	}
	//CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() + 10);
//else if (game->IsKeyDown(DIK_UP))
	//CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() - 10);
//{


//	}

	else //trạng thái đứng yên
	{
		// nên đặt biến is_shooting hay is_spin gì gì đó cho khỏi kẹp đk, nhiều đk vai lon
		/*if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
		{
			if(mario->GetState() == MARIO_STATE_FLY)

			else if(mario->GetState() == MARIO_STATE_)
		}*/
		if (mario->GetState() == MARIO_STATE_FLY)
			return;
		if (mario->GetState() == MARIO_STATE_FLY_HIGH)
			return;
		if (mario->GetState() == MARIO_STATE_SPIN)
			return;

		if (mario->GetState() == MARIO_STATE_JUMP_SHOOT_BULLET)
			return;
		if (mario->GetState() == MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT)
			return;

		float speed_x = abs(mario->vx);
		//DebugOut(L"co vo diz z? \n");
		//mario->is_press_z = true;

		if (speed_x > 0.2)
		{

			if (mario->nx > 0)
			{
				DebugOut(L"vo peed_x > 0.4 khong mario->nx > 0 \n");
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(-1.8 * MARIO_ACCELERATION);

			}
			else if (mario->nx < 0)
			{
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(1.8 * MARIO_ACCELERATION);
				DebugOut(L"vo tru bu luon moi ge \n");
			}

		}
		else
		{

			mario->is_slightly_lower_limit = false;
			//mario->SetState(MARIO_STATE_IDLE);
			mario->is_skid = false;
			mario->is_max_speed = false;
			mario->is_left = false;
			mario->is_right = false;
			//mario->is_walking = false;

			//DebugOut(L"helooo , zo idle hemmmmmmmmmmm: \n");
			mario->SetIsFly(false);



			if (mario->GetState() == MARIO_STATE_SHOOT_BULLET)
				return;

			mario->SetState(MARIO_STATE_IDLE);

		}

		mario->is_fly_high = false;
		mario->is_fly_short = false;

		//	{

		//	}

		//	if (mario->GetState() != MARIO_STATE_SHOOT_BULLET&&mario->GetIsInObject() == true)
		//		mario->SetState(MARIO_STATE_IDLE);

		//	if (mario->GetState() != MARIO_STATE_FLY_SHOOT_BULLET && mario->GetIsInObject()==false )
		//		mario->SetState(MARIO_STATE_IDLE);


	}
}