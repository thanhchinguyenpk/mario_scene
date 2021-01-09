#include "CoinEffect.h"

CoinEffect::CoinEffect(float brickX, float brickY)
{
	x = brickX;
	y = brickY;

	minPosY = brickY - 48 * 3;
	maxPosY = brickY;

	CAnimationSets * animation_sets_temp = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets_temp->Get(14);
	this->SetAnimationSet(ani_set);

	vy = -0.5;

}

void CoinEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	Effect::Update(dt, coObjects);

	y += dy;
	if (y < minPosY&&make_sure_go_down==false)
	{
		vy = -vy;
		make_sure_go_down = true;// có trường hợp lên cái bị khựng lại và lên luon, nên kẹp biến này cho chắc
	}
	if (y > maxPosY && vanish == false)
	{
		vanish = true;
		effect = new MoneyEffect(this->x,this->y-50);
	}

	if (effect)
	{
		effect->Update(dt, coObjects);
		if (effect->used == true)
		{
			delete effect;
			effect = NULL;
		}
	}
}

void CoinEffect::Render()
{
	if (vanish == false)
		animation_set->at(0)->Render(x, y, 0, 255, nx, ny);

	if (effect)
		effect->Render();
}
void CoinEffect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}
