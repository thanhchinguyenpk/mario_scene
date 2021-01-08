#include "RandomBonus.h"


RandomBonus::RandomBonus(CMario *player)
{
	mario = player;
	start_ani = GetTickCount64(); 
	SetState(STATE_RANDOM_BONUS_FIRE_FLOWER);
}

void RandomBonus::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt, colliable_objects);

	if (got_bonus == false)
	{
		float mt, ml, mb, mr, l, t, r, b;
		mario->GetBoundingBox(ml, mt, mr, mb);
		this->GetBoundingBox(l, t, r, b);
		if (this->CheckOverLap(ml, mt, mr, mb, l, t, r, b))
		{
			DebugOut(L"va chạm rùi hihi object type: %d\n");
			got_bonus = true;
			time_order_to_render_text = GetTickCount64();
			
			mario->is_hit_bonus = true;

		}
	}
	

	if (GetTickCount64() - start_ani >=2000&&got_bonus==false)
	{
		
		/*if (state == STATE_RANDOM_BONUS_MUSHROOM)
		{
			DebugOut(L"[ERR]1 vô đây? object type: %d\n");
			SetState(STATE_RANDOM_BONUS_STAR);
		}
		else if (state == STATE_RANDOM_BONUS_STAR)
		{
			SetState(STATE_RANDOM_BONUS_FIRE_FLOWER);
			DebugOut(L"[ERR]2 vô đây? object type: %d\n");
		}
		else if (state == STATE_RANDOM_BONUS_FIRE_FLOWER);
			SetState(STATE_RANDOM_BONUS_MUSHROOM);*/

		switch (state) {

		case STATE_RANDOM_BONUS_MUSHROOM:
			SetState(STATE_RANDOM_BONUS_STAR);
			break;
		case STATE_RANDOM_BONUS_STAR:
			SetState(STATE_RANDOM_BONUS_FIRE_FLOWER);
			break;
		case STATE_RANDOM_BONUS_FIRE_FLOWER:
			SetState(STATE_RANDOM_BONUS_MUSHROOM);
			break;
		}

			start_ani = GetTickCount64();

	} else if (got_bonus == true)
	{

		CGame* game = CGame::GetInstance();
		CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
		scene->is_mario_got_card = true;
		//scene->card = state+1;

		switch (state) {
		case STATE_RANDOM_BONUS_MUSHROOM:
			SetState(STATE_GOT_BONUS_MUSHROOM);
			cart_after_text = 1;
			scene->card = 1;
			//scene->mario_end_bonus = MUSHROOM_CARD;
			break;
		case STATE_RANDOM_BONUS_FIRE_FLOWER:
			SetState(STATE_GOT_BONUS_FIRE_FLOWER);
			cart_after_text = 2;
			scene->card = 2;
			//scene->mario_end_bonus = FIRE_FLOWER_CARD;
			break;
		case STATE_RANDOM_BONUS_STAR:
			SetState(STATE_GOT_BONUS_STAR);
			cart_after_text = 3;
			scene->card = 3;
			//scene->mario_end_bonus = STAR_MAN_CARD;
			break;
		
		}

		y += dy;
		x += dx;
	}
	
}

void RandomBonus::Render()
{
	int ani = 0;

	if (state == STATE_RANDOM_BONUS_MUSHROOM)
		ani = ANI_BONUS_MUSHROOM;
	else if (state == STATE_RANDOM_BONUS_STAR)
		ani = ANI_BONUS_STAR;
	else if (state == STATE_RANDOM_BONUS_FIRE_FLOWER)
		ani = ANI_BONUS_FIRE_FLOWER;
	else if (state == STATE_GOT_BONUS_MUSHROOM)
		ani = ANI_GOT_BONUS_MUSHROOM;
	else if (state == STATE_GOT_BONUS_STAR)
		ani = ANI_GOT_BONUS_STAR;
	else if (state == STATE_GOT_BONUS_FIRE_FLOWER)
		ani = ANI_GOT_BONUS_FIRE_FLOWER;


	//CAnimationSets* sets = CAnimationSets::GetInstance();
	//sets->Get(25)->at(0)->Render(8064 - 15, 1008 - 15, 255, 1, 0);
	
	//viiền họp quà
	CSprites::GetInstance()->Get(40040)->DrawFlipX(8088,1029, 0, 255, 1, 1);
	// quà bên trong random
	animation_set->at(ani)->Render(x, y, 0, 255, 1, 1);

	if (got_bonus == true)
	{
		float x = CGame::GetInstance()->GetCamX();
		float y = CGame::GetInstance()->GetCamY();

		if(GetTickCount64()- time_order_to_render_text>1000)
			text.Render(x + 200, y + 100, "COURSE CLEAR !");

		if (GetTickCount64() - time_order_to_render_text > 1500)
			text.Render(x + 170, y + 155, "YOU GOT A CARD");

		if (GetTickCount64() - time_order_to_render_text > 2000)
			CSprites::GetInstance()->Get(40040+cart_after_text)->DrawFlipX(x+550,y+ 155, 0, 255, 1, 1);

		//TextAndNumber text;
		//CSprites::GetInstance()->Get(40040 )->DrawFlipX(x + 100, y + 155, 0, 255, 1, 1);
	}
		

	RenderBoundingBox();
}

void RandomBonus::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state) {
	case STATE_GOT_BONUS_MUSHROOM:
	case STATE_GOT_BONUS_STAR:
	case STATE_GOT_BONUS_FIRE_FLOWER:
		vy = -0.3;
		break;
	}
}

void RandomBonus::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - RANDOMBONUS_BBOX_WIDTH / 2;
	top = y - RANDOMBONUS_BBOX_HEIGHT / 2;
	right = x + RANDOMBONUS_BBOX_WIDTH / 2;
	bottom = y + RANDOMBONUS_BBOX_HEIGHT / 2;
}
