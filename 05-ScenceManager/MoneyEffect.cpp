#include "MoneyEffect.h"

MoneyEffect::MoneyEffect(int pos_x, int pos_y, int moneyAni)
{
	this->x = pos_x;
	this->y = pos_y;

	vy = -0.15;
	effectTime = 300;

	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(23));
}

void MoneyEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	Effect::Update(dt, coObjects);
	y += dy;
}

void MoneyEffect::Render()
{
	animation_set->at(0)->Render(x, y, 0, 255, nx, ny);
}

MoneyEffect::~MoneyEffect()
{
}
