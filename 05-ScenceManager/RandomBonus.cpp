#include "RandomBonus.h"
#include "debug.h"

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
	}if (got_bonus == true)

	{
		switch (state) {
		case STATE_RANDOM_BONUS_MUSHROOM:
			SetState(STATE_GOT_BONUS_MUSHROOM);
			//scene->mario_end_bonus = MUSHROOM_CARD;
			break;
		case STATE_RANDOM_BONUS_STAR:
			SetState(STATE_GOT_BONUS_STAR);
			//scene->mario_end_bonus = STAR_MAN_CARD;
			break;
		case STATE_RANDOM_BONUS_FIRE_FLOWER:
			SetState(STATE_GOT_BONUS_FIRE_FLOWER);
			//scene->mario_end_bonus = FIRE_FLOWER_CARD;
			break;
		}
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
	

	animation_set->at(ani)->Render(x, y, 0, 255, 1, 1);
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
