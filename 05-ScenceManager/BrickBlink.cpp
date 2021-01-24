#include "BrickBlink.h"
#include "DebrisBrick.h"

//extern vector<LPGAMEOBJECT> objects;

BrickBlink::BrickBlink(CMario * player)
{
	mario = player;
	type = 2;
}

void BrickBlink::Render()
{

	for (LPGAMEOBJECT debris : vec_debris)
		debris->Render();

	int ani = BRICK_BLINK_ANI_BLINK;
	int direction = 1;
	int ny = 1;
	if (is_brick == false)
		ani = BRICK_BLINK_ANI_COIN;

	if (vanish==false)
	animation_set->at(ani)->Render(x, y, 0, 255, direction, ny);
	//RenderBoundingBox();
}

void BrickBlink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (vanish)
		return;
	//if (is_brick == false)
	//	return;

	l = x - BRICK_BLINK_BBOX_WIDTH/2;
	t = y - BRICK_BLINK_BBOX_HEIGHT/2;
	r = x + BRICK_BLINK_BBOX_WIDTH/2;
	b = y + BRICK_BLINK_BBOX_HEIGHT/2;
}

void BrickBlink::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_BLINK_STATE_WAS_HIT:
	{
		float pos_x = this->x;
		float pos_y = this->y;

		DebrisBrick* debrick_brick = NULL;

		debrick_brick = new DebrisBrick(pos_x + DEBRIS_DISTANCE, pos_y - DEBRIS_DISTANCE, 1, 1.5);
		vec_debris.push_back(debrick_brick);


		debrick_brick = new DebrisBrick(pos_x + DEBRIS_DISTANCE, pos_y + DEBRIS_DISTANCE, 1, 1);
		vec_debris.push_back(debrick_brick);


		debrick_brick = new DebrisBrick(pos_x - DEBRIS_DISTANCE, pos_y + DEBRIS_DISTANCE, -1, 1);
		vec_debris.push_back(debrick_brick);

		debrick_brick = new DebrisBrick(pos_x - DEBRIS_DISTANCE, pos_y - DEBRIS_DISTANCE, -1, 1.5);
		vec_debris.push_back(debrick_brick);

		//this->used = true;
		vanish = true;
		//used = true;
	}
		break;

	case BRICK_BLINK_STATE_TRANSFORM:
		is_brick = !is_brick;

		
	}

}

void BrickBlink::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);



	mario->GetBoundingBox(ml, mt, mr, mb);

	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	{
		mario->score += 10;
		if (this->is_brick == true)
		{
			
			SetState(BRICK_BLINK_STATE_WAS_HIT);
		}
		else
			this->used=true;
	}	

	for (LPGAMEOBJECT debris : vec_debris)
	{
		debris->Update(dt, coObjects);
		if (debris->used)
			number_debris++;
	}

	if (number_debris == 4)
		this->used = true;
	
}
