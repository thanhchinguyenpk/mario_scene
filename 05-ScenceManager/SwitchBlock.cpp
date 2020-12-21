#include "SwitchBlock.h"
#include "BrickBlink.h"
#include "debug.h"

void SwitchBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state != SWITCH_BLOCK_STATE_WAS_PRESSED)
	{
		l = x - SWITCH_BLOCK_BBOX_WIDTH / 2;
		t = y - SWITCH_BLOCK_BBOX_HEIGHT / 2;
		r = x + SWITCH_BLOCK_BBOX_WIDTH / 2;
		b = y + SWITCH_BLOCK_BBOX_HEIGHT / 2;
	}

}

void SwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (time_to_retransform->IsTimeUp()&& transform_one_time==false)
	{
		SetState(SWITCH_BLOCK_STATE_WAS_PRESSED);
		transform_one_time = true;
		DebugOut(L"[ERROR--------vo press?--------------------] day la sizeeeeeee:  %d\n");
	}
}

void SwitchBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SWITCH_BLOCK_STATE_INIT:
		break;
	case SWITCH_BLOCK_STATE_WAS_PRESSED:
		StartTransformListBrick(&listBricks);
		time_to_retransform->StartTime();
		break;

	}
}

void SwitchBlock::Render()
{
	int ani = 0;
	int direction = 1;
	int ny = 1;
	if (state==SWITCH_BLOCK_STATE_WAS_PRESSED)
		ani = 1;
	animations[ani]->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}

void SwitchBlock::StartTransformListBrick(vector<LPGAMEOBJECT>* listBricks)
{
	for (UINT i = 0; i < listBricks->size(); i++)
	{
		listBricks->at(i)->SetState(BRICK_BLINK_STATE_TRANSFORM);
	}
}
