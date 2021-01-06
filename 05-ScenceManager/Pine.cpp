#include "Pine.h"

void Pine::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x - PINE_BBOX_WIDTH / 2;
	t = y - PINE_BBOX_HEIGHT / 2;
	r = x + PINE_BBOX_WIDTH / 2;
	b = y + PINE_BBOX_HEIGHT / 2;
}

void Pine::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Pine::SetState(int state)
{
	CGameObject::SetState(state);

	/*switch (state)
	{
	case PARA_GROOMBA_STATE_MOVE_LEFT:
		vx = PARA_GROOMBA_WALKING_SPEED;
		vy = 0;
		break;
	case PARA_GROOMBA_STATE_MOVE_RIGHT:
		vx = -PARA_GROOMBA_WALKING_SPEED;
		break;
	case PARA_GROOMBA_STATE_JUMP_SMALL:
		vy = -PARA_GROOMBA_WALKING_SPEED;
		break;
	}*/
}

void Pine::Render()
{
	int ani = 0;
	if (state == PINE_STATE_TALL)
		ani = 0;
	else if (state == PINE_STATE_SHORT)
		ani = 1;
	else if (state == PINE_STATE_BLACK)
		ani = 2;

	animation_set->at(ani)->Render(x, y, 0, 255, 1, 1);
	RenderBoundingBox();
}
