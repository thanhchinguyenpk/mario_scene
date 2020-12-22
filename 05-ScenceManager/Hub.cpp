#include "Hub.h"
#include "Game.h"

Hub::Hub(CMario* player)
{
	mario = player;
	pmeter = new Pmeter(player);

	CAnimationSets * animation_sets_temp = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets_temp->Get(27);
	pmeter->SetAnimationSet(ani_set);

}

void Hub::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void Hub::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Hub::SetState(int state)
{
}

void Hub::Render()
{
	
	pmeter->Render();
	//animations[0]->Render(x, y, 0, 255, 1, 1);

	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();
	CSprites::GetInstance()->Get(60010)->DrawFlipX(x + 20 + 76 * 3, y + 730 - 100 + 10 + 5);
}
