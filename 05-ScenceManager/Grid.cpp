#include "Grid.h"
#include "Goomba.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <fstream>
#include "debug.h"
#include "PlayScence.h"


#include "Utils.h"


void CGrid::Classify(LPGAMEOBJECT obj)
{
	enemies.push_back(obj);
}

void CGrid::GetListObjInGrid(float cam_x, float cam_y)
{
	CGame* game = CGame::GetInstance();
	enemies.clear();

	int top = (int)((cam_y) / CELL_HEIGHT);
	int bottom = (int)((cam_y + 730) / CELL_HEIGHT);

	int left = (int)((cam_x) / CELL_WIDTH);
	int right = (int)((cam_x + 760) / CELL_WIDTH);

	for (int i = top - 1; i <= bottom + 1; i++)
		for (int j = left - 1; j <= right + 1; j++) {
			if (j < 0) j = 0;
			if (i < 0) i = 0;
			/*DebugOut(L"i %d\n", i);
			DebugOut(L"j %d\n", j);
			DebugOut(L"size %d\n", cells[i][j].size());*/

			for (int k = 0; k < cells[i][j].size(); k++) {
				DebugOut(L"id %d\n", cells[i][j].at(k)->id_grid);
				//if (cells[i][j].at(k)->GetHealth()) {
				if (cells[i][j].at(k)->is_appeared == false&& cells[i][j].at(k)->used==false)
					//{//  && 
					//if (j >= left && j <= right)
				{
					Classify(cells[i][j].at(k));
					cells[i][j].at(k)->is_appeared = true;
				}
				//}
					//if (!cells[i][j].at(k)->is_in_grid && cells[i][j].at(k)->is_appeared) {
				
					//	cells[i][j].at(k)->is_in_grid = true;
				//	}

				//}
			}
		}

	game->GetCurrentScene()->SetEnemiesInScene(enemies);
	//game->GetCurrentScene()->SetEnemiesInScene(enemies);

}

void CGrid::UpdatePositionInGrid(float cam_x, float cam_y)
{
	CGame* game = CGame::GetInstance();
	int top_cell = (int)((cam_y) / CELL_HEIGHT);
	int bottom_cell = (int)((cam_y + game->GetScreenHeight()) / CELL_HEIGHT) - 1;

	int left_cell = (int)((cam_x) / CELL_WIDTH);
	int right_cell = (int)((cam_x + game->GetScreenWidth()) / CELL_WIDTH);
	enemies.clear();
	//items.clear();


	CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
	enemies = scene->enemies;
	//items = scene->items;
	// update  vị trí của enemy trong cam từ cell này qua cell khác
	// chõ này Phương xóa ra khỏi cell rồi đặt vô?
	for (int m = 0; m < enemies.size(); m++) {
		LPGAMEOBJECT enemy = enemies[m];

		for (int i = top_cell - 1; i <= bottom_cell + 1; i++)
			for (int j = left_cell +1; j <= right_cell-1; j++) {
				if (j < 0) j = 0;
				if (i < 0) i = 0;
				for (int k = 0; k < cells[i][j].size(); k++) {
					if (cells[i][j].at(k)->id_grid == enemy->id_grid) {
						cells[i][j].erase(cells[i][j].begin() + k);
					}
				}
			}

		int top = (int)(enemy->GetY() / CELL_HEIGHT);
		int bottom = (int)((enemy->GetY() + enemy->h) / CELL_HEIGHT);
		int left = (int)(enemy->GetX() / CELL_WIDTH);
		int right = (int)((enemy->GetX() + enemy->w) / CELL_WIDTH);

		//DebugOut(L"left %d\n", left);
		//DebugOut(L"right %d\n", right);
		for (int i = top; i <= bottom; i++)
			for (int j = left; j <= right; j++) {
				cells[i][j].push_back(enemy);
			}
	}

	




}

LPGAMEOBJECT CGrid::CreateNewObj(int obj_type, float x, float y, float w, float h, int ani_id, int type, int extra, int nx, int angle, int id_grid)
{
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (obj_type)
	{

	case 2:
		{
			obj = new CGoomba(player);
			obj->SetState(GOOMBA_STATE_WALKING);
			break;
		}
	case 7:
	{
		int lv =type;
		obj = new VenusFireTrap(player, lv);
		//obj->SetState(VENUS_STATE_GOING_UP);
		break;
	}
	case 8:
	{
		//int lv = atof(tokens[4].c_str());
		obj = new PiranhaPlant(player);
		//obj->SetState(PIRANHA_PLANT_STATE_GOING_UP);
		break;
	}

	case 4:

	{
		obj = new CConCo(player, y);
		dynamic_cast<CConCo*>(obj)->type = type; //loại cò
		break;
	}
	case 5:
	{
		obj = new ParaGoomba(player);
		//obj->SetState(PARA_GROOMBA_STATE_JUMP_BIG);
		break;
	}



	}


	obj->SetPosition(x, y);
	obj->w = w;
	obj->h = h;
	obj->id_grid = id_grid;

	LPANIMATION_SET ani_set = animation_sets->Get(ani_id);
	// nhớ thêm đoạn code animation set mà null chẳng hạn 0:32:38
	obj->SetAnimationSet(ani_set);

	return obj;
	//return NULL;
}

void CGrid::ReadFileObj()
{
	ifstream f;
	f.open(objFilePath);
	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<string> tokens = split(line);
		if (line[0] == '#') {
			continue;
		}
		if (tokens.size() < 8) continue;
		int id_grid = atoi(tokens[0].c_str());
		int object_type = atoi(tokens[1].c_str());
		float x = atof(tokens[2].c_str());
		float y = atof(tokens[3].c_str());

		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());

		int ani_id = atoi(tokens[6].c_str());


		int type = atoi(tokens[7].c_str());
		int extra = 0;
		if (object_type == 2 || object_type == 3 ||
			object_type == 6 || object_type == 11 ||
			object_type == 1)
			extra = atoi(tokens[8].c_str());

		//AddObjectIntoGrid(object_type, x, y, w, h, ani_id, type, extra);
		LPGAMEOBJECT obj = CreateNewObj(object_type, x, y, w, h, ani_id, type, extra, 1, 1, id_grid);
		total_obj.push_back(obj);
	}

	f.close();
}

void CGrid::ReadFileGrid()
{
	//objs.clear();
	ifstream f;
	f.open(gridFilePath);
	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<string> tokens = split(line);
		if (line[0] == '#') {
			continue;
		}
		if (tokens.size() < 3) continue;
		int i = atoi(tokens[0].c_str());
		int j = atoi(tokens[1].c_str());
		for (int k = 2; k < tokens.size(); k++) {
			int id = atoi(tokens[k].c_str());
			for (LPGAMEOBJECT obj : total_obj)
				if (obj->id_grid == id) {
					cells[i][j].push_back(obj);
				}

		}
	}

	f.close();

	//DebugOut(L"[EEEEEEEEEEEEEEE] DINPUT::GetDeviceData failed. Error: %d\n", cells[6][14].size());
}

CGrid::CGrid(LPCWSTR objFilePath, LPCWSTR gridFilePath, CMario *mario)
{
	//DebugOut(L"new\n");
	this->objFilePath = objFilePath;
	this->gridFilePath = gridFilePath;

	player = mario;
}
