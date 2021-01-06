#include "ConCo.h"
#include "Game.h"
#include "debug.h"
#include "Flatform.h"
#include "Brick.h"


#include "Utils.h"


void CConCo::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x- (float)CONCO_BBOX_WIDTH/2;
	top = y- (float)CONCO_BBOX_HEIGHT/2;
	right = x + (float)CONCO_BBOX_WIDTH/2;

	if (state == CONCO_STATE_DIE) // chua ok
		bottom = y + (float)CONCO_BBOX_HEIGHT_DIE/2;
	else
		bottom = y + (float)CONCO_BBOX_HEIGHT/2;

	if (state == CONCO_STATE_THUT_VAO||state==CONCO_STATE_MAI_RUA_CHAY_PHAI|| state == CONCO_STATE_MAI_RUA_CHAY_TRAI
		|| state == CONCO_STATE_INDENT_OUT
		|| state == CONCO_STATE_SHELL_MOVING)
	{
		left = x - (float)16*3/2;// ủa tại sao để define thì lại lỗi ????
		top = y - (float)17*3/2;
		right = x + (float)16*3/2;
		bottom = y + (float)17*3/2;
	}
}

void CConCo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	if (is_brought == false)
	{
		CGameObject::Update(dt, coObjects);
	}

	vy += 0.002 * dt;

	


	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();


	//if đã nha nếu mà nấm khác với nấm biến mất thì
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0|| state==CONCO_STATE_WAS_SHOOTED)
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
			//vx = 0;
			if (state == CONCO_STATE_WALKING_LEFT)
			{
				SetState(CONCO_STATE_WALKING_RIGHT);
				//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] cham dau quay qua phải. Error: \n");
			}
			else if (state == CONCO_STATE_WALKING_RIGHT)
			{
				SetState(CONCO_STATE_WALKING_LEFT);
				//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] cham dau quay qua trái. Error: \n");
			}
			else
				vx = -vx;
			//if(state==)
		}// tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
		if (ny != 0)
		{
			//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] co nhay vo phuong DOC Error: \n");
			if (state == CONCO_STATE_FLY_LEFT)
				vy = -0.6; // sẽ bị chặn lại_ không đúng má ơi.
			else
				vy = 0;
		}



		//int boQuaVienDaDongTienDauTienAnNap = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];


		

			if (dynamic_cast<Flatform*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
			{
				if (is_walking_back_and_fort == 1)
				{
					Flatform* flatform = dynamic_cast<Flatform*>(e->obj);

					if (this->x > flatform->x + 273 && state == CONCO_STATE_WALKING_RIGHT)
						SetState(CONCO_STATE_WALKING_LEFT);
					if (this->x < flatform->x &&state == CONCO_STATE_WALKING_LEFT)
						SetState(CONCO_STATE_WALKING_RIGHT);
					
				}	
			}

			if (dynamic_cast<BrickBlink*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
			{
				
				BrickBlink* brick_blink = dynamic_cast<BrickBlink*>(e->obj);
				

					if (this->x > brick_blink->x + 24 && state == CONCO_STATE_WALKING_RIGHT&& brick_blink->is_brick == true)
						SetState(CONCO_STATE_WALKING_LEFT);
					if (this->x < brick_blink->x-24 &&state == CONCO_STATE_WALKING_LEFT && brick_blink->is_brick == true)
						SetState(CONCO_STATE_WALKING_RIGHT);
					if (brick_blink->is_brick == false&&count_brick<2)
					{
						count_brick++;
						y += dy;
						SetState(CONCO_STATE_WALKING_RIGHT);
					}

					if ((state == CONCO_STATE_MAI_RUA_CHAY_PHAI || state == CONCO_STATE_MAI_RUA_CHAY_TRAI) && brick_blink->is_brick == true)

					{
						if (e->nx != 0) // phương va chạm hướng lên
						{
							brick_blink->SetState(BRICK_BLINK_STATE_WAS_HIT);
							//brick_blink->used = true;
						}
					}
							
						
				
			}



			}

		}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (state == CONCO_STATE_THUT_VAO && GetTickCount64() - time_to_indent_out > 4000)
	{
		SetState(CONCO_STATE_SHELL_MOVING);
		
	}

	if (state== CONCO_STATE_SHELL_MOVING && GetTickCount64() - time_to_indent_out > 6000)
		SetState(CONCO_STATE_INDENT_OUT);

	if (state == CONCO_STATE_INDENT_OUT && GetTickCount64() - time_to_indent_out > 7000)
	{
		SetPosition(this->x, this->y - 32);//để khi thọt ra mai rùa không bị rơi xuống
		SetState(CONCO_STATE_WALKING_LEFT);
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

void CConCo::Render()
{
	
	int ani = CONCO_ANI_WALKING_LEFT;
	if (state == CONCO_STATE_WALKING_RIGHT)
		ani = CONCO_ANI_WALKING_RIGHT;
	else if (state == CONCO_STATE_THUT_VAO || state == CONCO_STATE_WAS_SHOOTED)
		ani = CONCO_ANI_THUT_VAO;
	else if (state == CONCO_STATE_MAI_RUA_CHAY_PHAI|| state == CONCO_STATE_MAI_RUA_CHAY_TRAI)
		ani = CONCO_ANI_MAI_RUA_CHAY;
	else if (state == CONCO_STATE_INDENT_OUT)
		ani = CONCO_ANI_INDENT_OUT;
	else if (state == CONCO_STATE_SHELL_MOVING)
		ani = CONCO_ANI_SHELL_MOVING;
	else if (state == CONCO_STATE_FLY_LEFT)
		ani = CONCO_ANI_FLY_LEFT; // thôi kệ nó đi :(

	if (effect)
		effect->Render();

	//int ani = CONCO_ANI_THUT_VAO;
	//DebugOut(L"[ERROR-------state cua con co------------------] DINPUT::GetDeviceData failed. Error: %d\n", state);
	//animation_set->at(0)
		animation_set->at(ani)->Render(x, y,0,255,1,1);
	RenderBoundingBox();
}

void CConCo::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONCO_STATE_DIE:
		y += CONCO_BBOX_HEIGHT - CONCO_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case CONCO_STATE_WALKING_LEFT:
		vx =  -CONCO_WALKING_SPEED;
		nx = -1;
		break;
	case CONCO_STATE_WALKING_RIGHT:
		vx = CONCO_WALKING_SPEED;
		nx = 1;
		break;
	case CONCO_STATE_THUT_VAO:
		vx = 0;
		vy = 0;
		nx = 1;
		time_to_indent_out = GetTickCount64();

		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y-50);
		//y = 135;
		break;
	case CONCO_STATE_MAI_RUA_CHAY_PHAI:
		vx = 8*CONCO_MAI_RUA_CHAY_SPEED;
		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y-50);
		break;
	case CONCO_STATE_MAI_RUA_CHAY_TRAI:
		vx = -8 * CONCO_MAI_RUA_CHAY_SPEED;
		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y-50);
		break;
	case CONCO_STATE_FLY_LEFT:
		vx = -CONCO_WALKING_SPEED;// -0.13;
		//vy = 0;
		nx = -1;
		vx = 0;
		vy = 0;
		break;
	case CONCO_STATE_FLY_RIGHT:
		vx = CONCO_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;// 0.1f * 1.5;
		vy = 0;
		//nx = 1;
		break;
	case CONCO_STATE_WAS_SHOOTED:
		vx = -vx;// 0.1f * 1.5;
		vy = -0.25*3;
		ny = -1;
		//nx = 1;
		break;
	case CONCO_STATE_INDENT_OUT:

		break;
	case CONCO_STATE_SHELL_MOVING:

		break;

	}
}

