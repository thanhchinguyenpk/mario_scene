#include "Brick_Coin.h"
#include <dinput.h>
#include "debug.h"
#include "Mushroom.h"
#include "SwitchBlock.h"

//extern vector<LPGAMEOBJECT> objects;

void Brick_Coin::Render()
{
	int ani = 0;

	 if (state == BRICK_COIN_STATE_DA_DAP)
		ani = 1;
	 else if(is_contain_button_p)
		 ani = 2;
	//DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", ani);


	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}



void Brick_Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;

	if (state != BRICK_COIN_STATE_DA_DAP) 
	{
		float ml, mt, mr, mb;
		float il, it, ir, ib;

		this->GetBoundingBox(il, it, ir, ib);



		mario->GetBoundingBox(ml, mt, mr, mb);

		if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
		{
			SetState(BRICK_COIN_STATE_DA_DAP);
			
		}
	}


	if (y<originalY-20 && flag==false)
	{
		vy = -vy;
		flag = true;
	}
	
	 else if ( flag==true && y>=originalY)
	{
		//DebugOut(L"[ERROR-------vy của viên gạch-----------------] DINPUT::GetDeviceData failed. Error: %f\n",y);
		
		vy = 0;
		y = originalY;
		is_hit = true;
		//flag = false;
	}
	
	//DebugOut(L"[ERROR-------vy của viên gạch-----------------] DINPUT::GetDeviceData failed. Error: %f\n", originalY);
}

void Brick_Coin::SetState(int state)
{

	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_COIN_STATE_DA_DAP:
		vy = -0.2;
		{
		/*Mushroom* mr = new Mushroom(this->x,this->y);
		//mr->AddAnimation(11001);
		mr->AddAnimation(21000);
		mr->SetPosition(this->x, this->y);
		mr->SetState(MUSHROOM_STATE_GOING_UP);
		itemsMarioCanEat.push_back(mr);*/

			/*CGame* game = CGame::GetInstance();
			CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
			scene->is_mario_got_card = true;*/

			if (is_contain_button_p == 1)
			{
				SwitchBlock* switch_block = new SwitchBlock();
				switch_block->SetAnimationSet(CAnimationSets::GetInstance()->Get(21));
				switch_block->SetState(SWITCH_BLOCK_STATE_INIT);
				switch_block->SetPosition(this->x, this->y - SWITCH_BLOCK_BBOX_HEIGHT);

				CGame* game = CGame::GetInstance();
				CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
				scene->objects.push_back(switch_block);
				//objects.push_back(switch_block);
			}
			
		}
	
		break;
	/*case BRICK_COIN_STATE_BOUCING:
		is_hit = true;
		break;*/
	
	}

}

Brick_Coin::Brick_Coin(float pos_y, CMario * player, int is_has_button_p, int type_brick)
{
	// originalX = x;
	 mario = player;
	 this->originalY = pos_y;
	 is_contain_button_p = is_has_button_p;
	 brick_type = type_brick;
}


void Brick_Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_COIN_BBOX_WIDTH / 2;
	t = y - BRICK_COIN_BBOX_HEIGHT / 2;
	r = x + BRICK_COIN_BBOX_WIDTH / 2;
	b = y + BRICK_COIN_BBOX_HEIGHT / 2;
}