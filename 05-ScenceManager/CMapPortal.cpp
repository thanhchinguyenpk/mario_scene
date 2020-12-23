#include "CMapPortal.h"

#define MAP_PORTAL_BBOX_WIDTH  16*3
#define MAP_PORTAL_BBOX_HEIGHT 16*3

CMapPortal::CMapPortal(int id, float x, float y, bool is_portal, int t, int r, int b, int l, int state)
{
	this->id_portal = id;
	this->x = x;
	this->y = y;

	this->is_portal = is_portal;
	this->l = l;
	this->t = t;
	this->r = r;
	this->b = b;

	this->state = state;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(26);
	SetAnimationSet(ani_set);
}

void CMapPortal::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x - MAP_PORTAL_BBOX_WIDTH / 2;
	t = y - MAP_PORTAL_BBOX_HEIGHT / 2;
	r = x + MAP_PORTAL_BBOX_WIDTH / 2;
	b = y + MAP_PORTAL_BBOX_HEIGHT / 2;
}

void CMapPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CMapPortal::Render()
{
	int ani = 8;
	switch (state) {
	case STATE_START:
		ani = ANI_START;
		break;
	case STATE_1:
		ani = ANI_1;
		break;
	case STATE_2:
		ani = ANI_2;
		break;
	case STATE_3:
		ani = ANI_3;
		break;
	case STATE_4:
		ani = ANI_4;
		break;
	case STATE_5:
		ani = ANI_5;
		break;
	case STATE_6:
		ani = ANI_6;
		break;
	case STATE_CARD:
		ani = ANI_CARD;
		break;
	case STATE_EMPTY:
		ani = ANI_EMPTY;
		break;
	}
	animation_set->at(ani)->Render(x , y , 0, 255, nx, ny);

	RenderBoundingBox();
}
