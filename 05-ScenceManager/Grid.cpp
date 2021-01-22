#include "Grid.h"

void CGrid::Classify(LPGAMEOBJECT obj)
{
	enemies.push_back(obj);
}

void CGrid::GetListObjInGrid(float cam_x, float cam_y)
{
	CGame* game = CGame::GetInstance();
	enemies.clear();

	int top = (int)((cam_y) / CELL_HEIGHT);
	int bottom = (int)((cam_y + game->GetScreenHeight()) / CELL_HEIGHT) - 1;

	int left = (int)((cam_x) / CELL_WIDTH);
	int right = (int)((cam_x + game->GetScreenWidth()) / CELL_WIDTH);

	for (int i = top - 1; i <= bottom + 1; i++)
		for (int j = left - 1; j <= right + 1; j++) {
			if (j < 0) j = 0;
			if (i < 0) i = 0;
			/*DebugOut(L"i %d\n", i);
			DebugOut(L"j %d\n", j);
			DebugOut(L"size %d\n", cells[i][j].size());*/

			for (int k = 0; k < cells[i][j].size(); k++) {
				//DebugOut(L"id %d\n", cells[i][j].at(k)->GetId());
				//if (cells[i][j].at(k)->GetHealth()) {
					//if (j >= left && j <= right)
						//cells[i][j].at(k)->is_appeared = true;
					//if (!cells[i][j].at(k)->is_in_grid && cells[i][j].at(k)->is_appeared) {
						Classify(cells[i][j].at(k));
					//	cells[i][j].at(k)->is_in_grid = true;
				//	}

				//}
			}
		}

	game->GetCurrentScene()->SetEnemiesInScene(enemies);
	//game->GetCurrentScene()->SetEnemiesInScene(enemies);

}

void CGrid::CreateNewObj(int obj_type, float x, float y, float w, float h, int ani_id, int type, int extra, int nx, int angle, int id_grid)
{
	/*CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (obj_type)
	{

	case 2:
		{
			//obj = new CGoomba(player);
			//obj->SetState(GOOMBA_STATE_WALKING);
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

	return obj;*/
	//return NULL;
}

CGrid::CGrid(LPCWSTR objFilePath, LPCWSTR gridFilePath)
{
	//DebugOut(L"new\n");
	this->objFilePath = objFilePath;
	this->gridFilePath = gridFilePath;

	//player = mario;
}
