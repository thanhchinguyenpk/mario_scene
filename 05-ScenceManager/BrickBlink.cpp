#include "BrickBlink.h"
#include "DebrisBrick.h"

extern vector<LPGAMEOBJECT> objects;

void BrickBlink::Render()
{
	int ani = BRICK_BLINK_ANI_BLINK;
	int direction = 1;
	int ny = 1;
	if (is_brick == false)
		ani = BRICK_BLINK_ANI_COIN;

	animations[ani]->Render(x, y, 0, 255, direction, ny);
	//RenderBoundingBox();
}

void BrickBlink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
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
		objects.push_back(debrick_brick);


		debrick_brick = new DebrisBrick(pos_x + DEBRIS_DISTANCE, pos_y + DEBRIS_DISTANCE, 1, 1);
		objects.push_back(debrick_brick);


		debrick_brick = new DebrisBrick(pos_x - DEBRIS_DISTANCE, pos_y + DEBRIS_DISTANCE, -1, 1);
		objects.push_back(debrick_brick);

		debrick_brick = new DebrisBrick(pos_x - DEBRIS_DISTANCE, pos_y - DEBRIS_DISTANCE, -1, 1.5);
		objects.push_back(debrick_brick);

		this->used = true;

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
			SetState(BRICK_BLINK_STATE_WAS_HIT);
	
}

BrickBlink::BrickBlink()
{
}
