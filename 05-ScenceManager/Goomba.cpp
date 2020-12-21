#include "Goomba.h"
#include "debug.h"
//#include "MarioBullet.h"
#include "Flatform.h"

CGoomba::CGoomba(CMario * player)
{
	this->mario = player;
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x- GOOMBA_BBOX_WIDTH/2;
	top = y- GOOMBA_BBOX_HEIGHT/2;
	right = x + GOOMBA_BBOX_WIDTH/2;
	bottom = y + GOOMBA_BBOX_HEIGHT/2;

		/*if (state == GOOMBA_STATE_DIE)*/

		
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	//x += dx;
	//y += dy;

	vy += GOOMBA_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();


	//if đã nha nếu mà nấm khác với nấm biến mất thì
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0|| state == GOOMBA_STATE_WAS_SHOOTED)
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
		
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;
		

		if (nx != 0)
		{
			//vx = 0;
			vx = -vx;
		//	DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] co nhay vo phuong ngang. Error: \n");
			//delete this;
		}// tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
		if (ny != 0)
		{
			//DebugOut(L"[ERROR~~~~~~~~~con cua vo day nhiu lan~~~~~~~~~~~~~~~~~] co nhay vo phuong DOC Error: \n");
			 // sẽ bị chặn lại_ không đúng má ơi.

			vy = 0;

			// tý dùng
			//vy = -0.25 * 3;
		}



		//int boQuaVienDaDongTienDauTienAnNap = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];
			

			//delete nó đi nè :D
			if (dynamic_cast<Flatform*>(e->obj) && state == GOOMBA_STATE_WAS_SHOOTED)
			{
				

			}
	
				/*	if (dynamic_cast<MarioBullet*>(e->obj))
					{
						SetState(GOOMBA_STATE_WAS_SHOOTED);
						//SetPosition(x, y - 20);
						DebugOut(L"[ERROR~~~~~~~~~~~~~~~~CO BAO GIO NHAY VO DAY k: \n");
					}
					*/

			

		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	

	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);


	//đoạn này phải chỉnh lại trong mario á huhu
	mario->GetBoundingBox(ml, mt, mr, mb);

	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb) && mario->GetState()== MARIO_STATE_SPIN)
		SetState(GOOMBA_STATE_WAS_SHOOTED);



	if (time_to_disapear->IsTimeUp())
		used = true;

	//DebugOut(L"[ERROR----------vy cua con cua-----------------] DINPUT::GetDeviceData failed. Error: %g\n", vy);
}

void CGoomba::Render()
{
	//int ny = 1;

	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	else if (state == GOOMBA_STATE_WAS_SHOOTED)
	{
		ani = GOOMBA_ANI_WAS_SHOOTED;
		ny = -1;
	}

	int alpha = 255;

	//animation_set->at(ani)->Render(x, y, 0, alpha, nx);
	animation_set->at(ani)->Render(x, y, 0, alpha, nx,ny);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			//y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			time_to_disapear->StartTime();
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -0.05;//GOOMBA_WALKING_SPEED;
			//vx = 0;
			//vy = 0;
			break;
		case GOOMBA_STATE_WAS_SHOOTED:
			vy = -0.25 * 3;
			//vx = 0;
			vx = -vx;
			ny = -1;
			break;
	}
}
