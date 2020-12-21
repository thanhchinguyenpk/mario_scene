#include "Brick.h"

void CBrick::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;// -BRICK_BBOX_WIDTH / 2;
	t = y;// -BRICK_BBOX_HEIGHT / 2;
	r = x + 9000;// BRICK_BBOX_WIDTH/2;
	b = y + BRICK_BBOX_HEIGHT/2;
}