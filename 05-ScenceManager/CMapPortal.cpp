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
	RenderBoundingBox();
}
