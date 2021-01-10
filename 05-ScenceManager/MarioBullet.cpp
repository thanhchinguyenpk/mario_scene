#include "MarioBullet.h"
#include "TimerCustom.h"
#include "debug.h"
#include "Goomba.h"
#include "ConCo.h"
#include "ParaGoomba.h"
#include "BoomerangBrother.h"

//#include "VenusFireTrap.h"

int is_delete = false;
extern vector<LPGAMEOBJECT> objects;


void MarioBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIOBULLET_BBOX_WIDTH;

	if (state == MARIOBULLET_STATE_DIE)
		bottom = y + MARIOBULLET_BBOX_HEIGHT_DIE;
	else
		bottom = y + MARIOBULLET_BBOX_HEIGHT;
}

void MarioBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	if (state != MARIOBULLET_STATE_BUM)
		 vy += MARIOBULLET_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear(); // ủa tại sao ở dưới delete rồi mà ở đây lại clear nữa?

	// turn off collision when die 
	if (state != MARIOBULLET_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	// tính ra danh sách các đối tượng có khả năng va chạm với mario


	// reset untouchable timer if untouchable time has passed




	// No collision occured, proceed normally
	// nếu như không có bất cứ va chạm nào
	if (coEvents.size() == 0)
	{
		x += dx; // quãng đường di chuyển thực sự trong frame , nếu như k có va chạm
		y += dy;
	}
	else // trong trường hợp có va chạm xẩy ra
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// filter đối tượng trên từng trục để xử lí va chạm

		// block // đẩy lùi ra so với chiều của các hướng bị va chạm, 0.4f là tránh bị trùng mép
		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

		
		
		if (nx != 0)
		{
			//state = MARIOBULLET_STATE_BUM;
			vy = 0;
			vx = 0;
			//is_disapear = true;
			this->used = true;
			
		}; // tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
			if (ny != 0) vy = -0.25*1.5;// tưng lên
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];

			////	if (dynamic_cast<Flatform*>(e->obj) && state == GOOMBA_STATE_WAS_SHOOTED)
				//	state = GOOMBA_STATE_DIE;

			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);
				//SetPosition(x, y - 20);
				DebugOut(L"[ERROR~~~~~~~~~~~~~~~~CO BAO GIO NHAY VO DAY k: \n");
			}

			if (dynamic_cast<CConCo*>(e->obj))
			{
				CConCo* conco = dynamic_cast<CConCo*>(e->obj);

				conco->SetState(CONCO_STATE_WAS_SHOOTED);
				//SetPosition(x, y - 20);
				DebugOut(L"[ERROR~~~~~~~~~~~~~~~~CO BAO GIO NHAY VO DAY k: \n");
			}

			if (dynamic_cast<ParaGoomba*>(e->obj))
			{
				ParaGoomba* para = dynamic_cast<ParaGoomba*>(e->obj);

				para->SetState(PARA_GROOMBA_STATE_WAS_SHOOTED);
				//SetPosition(x, y - 20);
				//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~CO BAO GIO NHAY VO DAY k: \n");
			}

			if (dynamic_cast<BoomerangBrother*>(e->obj))
			{
				BoomerangBrother* brother = dynamic_cast<BoomerangBrother*>(e->obj);

				brother->SetState(BROTHER_STATE_WAS_SHOOTED);
				//SetPosition(x, y - 20);
				//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~CO BAO GIO NHAY VO DAY k: \n");
			}
			
			
		


		}



	}

	
	DeleteWhenOutOfCam();

	
	/*if (is_delete == false && state == MARIOBULLET_STATE_BUM && animations[MARIOBULLET_ANI_BUM]->IsRenderDone())
		is_delete = true;

	if (is_delete == true)
	{
		objects.pop_back();
		delete this;
		
	}*/
	//DebugOut(L"[ERROR-----------vx-------------------] DINPUT::GetDeviceData failed. Error: %f\n", vx);
	//DebugOut(L"[ERROR-----------vy-------------------] DINPUT::GetDeviceData failed. Error: %f\n", vy);
	//DebugOut(L"[ERROR-----------vy-------------------] DINPUT::GetDeviceData failed. Error: %d\n", state);
}

void MarioBullet::Render()
{
	int ani = MARIOBULLET_ANI_WALKING;
	if (state == MARIOBULLET_STATE_DIE) {
		ani = MARIOBULLET_ANI_DIE;
	}
	else if(state ==MARIOBULLET_STATE_BUM)
		ani = MARIOBULLET_ANI_BUM;
	
	animation_set->at(0)->Render(x, y);
	//animations[ani]->Render(x, y);
	RenderBoundingBox();
}



void MarioBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIOBULLET_STATE_WALKING_RIGHT:
		vx = MARIOBULLET_WALKING_SPEED;
		break;
	case MARIOBULLET_STATE_WALKING_LEFT:
		vx = -MARIOBULLET_WALKING_SPEED;
		break;
	case MARIOBULLET_STATE_BUM:
			//animations[MARIOBULLET_ANI_BUM]->ResetCurrentFrame();
			//animations[MARIOBULLET_ANI_BUM]->StartTimeAnimation();
			break;
		//vy = 0.07;
	}
}

