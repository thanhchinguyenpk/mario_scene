#include "ConCo.h"
#include "Game.h"
#include "debug.h"
#include "Flatform.h"
#include "Brick.h"
#include "Brick_Coin.h"

#include "Utils.h"


CConCo::CConCo(CMario * player, float y)
{
	mario = player;
	orginal_y = y; 
	
}

void CConCo::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != CONCO_STATE_WAS_SHOOTED)
	{
		left = x - (float)CONCO_BBOX_WIDTH / 2;
		top = y - (float)CONCO_BBOX_HEIGHT / 2;
		right = x + (float)CONCO_BBOX_WIDTH / 2;

		if (state == CONCO_STATE_DIE) // chua ok
			bottom = y + (float)CONCO_BBOX_HEIGHT_DIE / 2;
		else
			bottom = y + (float)CONCO_BBOX_HEIGHT / 2;

		if (state == CONCO_STATE_THUT_VAO || state == CONCO_STATE_MAI_RUA_CHAY_PHAI || state == CONCO_STATE_MAI_RUA_CHAY_TRAI
			|| state == CONCO_STATE_INDENT_OUT
			|| state == CONCO_STATE_SHELL_MOVING)
		{
			left = x - (float)16 * 3 / 2;// ủa tại sao để define thì lại lỗi ????
			top = y - (float)14 * 3 / 2;// mai rùa hơi cao
			right = x + (float)16 * 3 / 2;
			bottom = y + (float)17 * 3 / 2;
		}
	}
	
}

void CConCo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (mario->x + mario->distance_to_set_state_enemy > this->x && this->is_cam_coming == false)
	{
		if(type==0||type==2)
			SetState(CONCO_STATE_WALKING_LEFT);
		else if(type==1)
			SetState(CONCO_STATE_FLY_LEFT);
		else if(type==3)
			SetState(CONCO_STATE_RED_FLY_Y);


		this->is_cam_coming = true;
	}

	if (this->is_cam_coming == true)

	{

		if (is_brought == false)
		{
			CGameObject::Update(dt, coObjects);
		}

		if( state!= CONCO_STATE_RED_FLY_Y)
			vy += 0.002 * dt;

		if (type == 3 && state == CONCO_STATE_RED_FLY_Y)
		{
			if (y > orginal_y + 300 && is_change_direction_vy == false)
			{
				vy = -vy;
				is_change_direction_vy = true;
			}
			if (y < orginal_y&&is_change_direction_vy == true)
			{
				vy = -vy;
				is_change_direction_vy = false;
			}
		}



		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();


		//if đã nha nếu mà nấm khác với nấm biến mất thì
		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0 || state == CONCO_STATE_WAS_SHOOTED)
		{
			if(type!=3)
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
					vy = -0.6f; // sẽ bị chặn lại_ không đúng má ơi.
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

						if(type==2)
							if (this->x > flatform->x + flatform->width && state == CONCO_STATE_WALKING_RIGHT)
								SetState(CONCO_STATE_WALKING_LEFT);
							else if (this->x < flatform->x &&state == CONCO_STATE_WALKING_LEFT)
								SetState(CONCO_STATE_WALKING_RIGHT);

					}
				}

				if (dynamic_cast<Brick_Coin*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
				{
					if (state == CONCO_STATE_MAI_RUA_CHAY_PHAI || state == CONCO_STATE_MAI_RUA_CHAY_TRAI)
					{
						Brick_Coin* brick_coin = dynamic_cast<Brick_Coin*>(e->obj);

						if (brick_coin->GetState() == BRICK_COIN_STATE_CHUA_DAP)
						{
							brick_coin->SetState(BRICK_COIN_STATE_DA_DAP);
							brick_coin->is_hit = true;
						}
					}
					


				}

				if (dynamic_cast<BrickBlink*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
				{

					BrickBlink* brick_blink = dynamic_cast<BrickBlink*>(e->obj);


					if (this->x > brick_blink->x + 24 && state == CONCO_STATE_WALKING_RIGHT && brick_blink->is_brick == true)
						SetState(CONCO_STATE_WALKING_LEFT);
					if (this->x < brick_blink->x - 24 && state == CONCO_STATE_WALKING_LEFT && brick_blink->is_brick == true)
						SetState(CONCO_STATE_WALKING_RIGHT);
					if (brick_blink->is_brick == false && count_brick < 2)
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

				if (state == CONCO_STATE_MAI_RUA_CHAY_PHAI || state == CONCO_STATE_MAI_RUA_CHAY_TRAI)
				{
					if (dynamic_cast<CGoomba*>(e->obj))
					{
						dynamic_cast<CGoomba*>(e->obj)->SetState(GOOMBA_STATE_WAS_SHOOTED);
					}
					if (dynamic_cast<CConCo*>(e->obj))
					{
						dynamic_cast<CConCo*>(e->obj)->SetState(CONCO_STATE_WAS_SHOOTED);
					}
					if (dynamic_cast<ParaGoomba*>(e->obj))
					{
						dynamic_cast<ParaGoomba*>(e->obj)->SetState(PARA_GROOMBA_STATE_WAS_SHOOTED);
					}
				}


			}

		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


		if (state == CONCO_STATE_THUT_VAO && GetTickCount64() - time_to_indent_out > 9000)
		{
			SetState(CONCO_STATE_SHELL_MOVING);

		}

		if (state == CONCO_STATE_SHELL_MOVING && GetTickCount64() - time_to_indent_out > 10000)
			SetState(CONCO_STATE_INDENT_OUT);

		if (state == CONCO_STATE_INDENT_OUT && GetTickCount64() - time_to_indent_out > 12000)
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


		if (mario->GetState() == MARIO_STATE_SPIN)
		{

			float ml, mt, mr, mb;
			float il, it, ir, ib;

			this->GetBoundingBox(il, it, ir, ib);
			mario->GetBoundingBox(ml, mt, mr, mb);

			if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
			{
				SetState(CONCO_STATE_WAS_SHOOTED);
			}
		}


	}

	if (y > 1290)
		used = true;
}

void CConCo::Render()
{
	
	int ani = CONCO_ANI_GREEN_WALKING_LEFT;
	if (type == 0||type==1)
	{
		if (state == CONCO_STATE_WALKING_RIGHT)
			ani = CONCO_ANI_GREEN_WALKING_RIGHT;
		else if (state == CONCO_STATE_THUT_VAO || state == CONCO_STATE_WAS_SHOOTED)
			ani = CONCO_ANI_GREEN_THUT_VAO;
		else if (state == CONCO_STATE_MAI_RUA_CHAY_PHAI || state == CONCO_STATE_MAI_RUA_CHAY_TRAI)
			ani = CONCO_ANI_GREEN_MAI_RUA_CHAY;
		else if (state == CONCO_STATE_INDENT_OUT)
			ani = CONCO_ANI_GREEN_INDENT_OUT;
		else if (state == CONCO_STATE_SHELL_MOVING)
			ani = CONCO_ANI_GREEN_SHELL_MOVING;
		else if (state == CONCO_STATE_FLY_LEFT)
			ani = CONCO_ANI_GREEN_FLY_LEFT; // thôi kệ nó đi :(
	}
	else if (type == 2|| type == 3)
	{
		ani = CONCO_ANI_RED_WALKING_LEFT;

		if (state == CONCO_STATE_WALKING_RIGHT)
			ani = CONCO_ANI_RED_WALKING_RIGHT;
		else if (state == CONCO_STATE_THUT_VAO || state == CONCO_STATE_WAS_SHOOTED)
			ani = CONCO_ANI_RED_THUT_VAO;
		else if (state == CONCO_STATE_MAI_RUA_CHAY_PHAI || state == CONCO_STATE_MAI_RUA_CHAY_TRAI)
			ani = CONCO_ANI_RED_MAI_RUA_CHAY;
		else if (state == CONCO_STATE_INDENT_OUT)
			ani = CONCO_ANI_RED_INDENT_OUT;
		else if (state == CONCO_STATE_SHELL_MOVING)
			ani = CONCO_ANI_RED_SHELL_MOVING;
		else if (state == CONCO_STATE_RED_FLY_Y)
			ani = CONCO_ANI_RED_FLY_LEFT; // thôi kệ nó đi :(

	}
	
	

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
		//vx = 0.15;
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
		//vx = -vx;// 0.1f * 1.5;
		vx = 0.06f;
		vy = -0.25f;
		ny = -1;
		//nx = 1;
		break;
	case CONCO_STATE_INDENT_OUT:

		break;
	case CONCO_STATE_SHELL_MOVING:

		break;
	case CONCO_STATE_RED_FLY_Y:
		vx = 0;
		vy = 0.13f;
		break;


		

	}
}

