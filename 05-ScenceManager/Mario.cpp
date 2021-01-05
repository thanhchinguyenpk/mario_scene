#include <algorithm>
#include "debug.h" 

#include "Mario.h"
#include "Game.h"
#include "Utils.h"
#include "Goomba.h"

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"


#include "Brick.h"
#include "Goomba.h"
#include "ConCo.h"
#include "Brick_Coin.h"
#include "Coin.h"
#include "CoinFly.h"
#include "Mushroom.h"
#include "Flatform.h"
#include "BrickBlink.h"
#include "SwitchBlock.h"
#include "ParaGoomba.h"
#include "MapScene.h"




//extern vector<LPGAMEOBJECT> objects;

CAnimationSets * animation_sets_temp = CAnimationSets::GetInstance();
CGameObject * temp = NULL;



void CMario::Attack()
{
	if (listWeapons.size() == 2)
		return;

	 temp= new MarioBullet();
	 
	LPANIMATION_SET ani_set = animation_sets_temp->Get(4);
	temp->SetAnimationSet(ani_set);

	if (this->GetNX() > 0)
	{
		temp->SetState(MARIOBULLET_STATE_WALKING_RIGHT);
		temp->SetPosition(this->GetX() + 10 + 5, this->GetY());
	}
	else
	{
		temp->SetState(MARIOBULLET_STATE_WALKING_LEFT);
		temp->SetPosition(this->GetX() - 5, this->GetY());
	}
	
	listWeapons.push_back(temp);


}

void CMario::CheckOverlapWithItems(vector<LPGAMEOBJECT>* itemsMarioCanEat)
{
	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(ml, mt, mr, mb);

	for (UINT i = 0; i < itemsMarioCanEat->size(); i++)
	{
		LPGAMEOBJECT item = itemsMarioCanEat->at(i);

		item->GetBoundingBox(il, it, ir, ib);

		if (this->CheckOverLap(ml, mt, mr, mb, il, it, ir, ib))
			item->used = true;
	}
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//is_in_portal = false;
	//CGameObject* temp = NULL;

	if (is_go_down_pine)
	{
		CGameObject::Update(dt);
		y += dy;

		if ((GetTickCount64() - go_down_pine_then_move_cam > 2000)&& go_down_pine_then_move_cam)
		{
			if(is_on_the_ground==false)
				this->SetPosition(6363 + 16, 1521);
			else
				this->SetPosition(2336 * 3, 360 * 3);

			is_on_the_ground = !is_on_the_ground;//truyền biến xử lý cam ở play scene;
			//this->SetPosition(6363 + 16, 1521);
			is_go_down_pine = false;
			go_down_pine_then_move_cam = 0;
		}
	}
	else if (is_moving_in_world_map)
	{
		CGameObject::Update(dt);
		//DebugOutTitle(L"04 - collision %0.1f, %0.1f", this->x, this->y);
		CGame* game_temp = CGame::GetInstance();
		MapScene* map_scene = (MapScene*)game_temp->GetCurrentScene();

		if (x >= map_scene->current_portal->x && vx > 0 || x <= map_scene->current_portal->x && vx < 0)
		{
			this->SetPosition(map_scene->current_portal->x, map_scene->current_portal->y);
			vx = 0;
		}
		else
			x += dx;

		if (y <= map_scene->current_portal->y && vy < 0 || y >= map_scene->current_portal->y && vy > 0)
		{
			this->SetPosition(map_scene->current_portal->x, map_scene->current_portal->y);
			vy = 0;
		}
		else
			y += dy;
	}
	else
	{
		float x_flatform = 0;
		float y_flatform = 0;

		float vy_flatform = 0;
		float vx_flatform = 0;


		float speed_vx = abs(vx);

		// Calculate dx, dy 
		CGameObject::Update(dt);

		for (int i = 0; i < listWeapons.size(); i++)
		{
			listWeapons[i]->Update(dt, coObjects);

		}
		for (int i = 0; i < listWeapons.size(); i++)
		{
			if (listWeapons[i]->used)
			{
				listWeapons.erase(listWeapons.begin() + i);
			}
		}

		if (this->y < 50)
			is_run_for_fly_high = false;

		//if (is_slightly_lower_than_zero == true)
			//false;
		//is_increase_speed==true, liên quan ở vòng if
		if (is_press_z == true && is_fly == false && state != MARIO_STATE_SPIN && state != MARIO_STATE_SHOOT_BULLET
			&& state != MARIO_STATE_JUMP_SHOOT_BULLET) //không phải là bay, nếu bay là nó bay có gia tốc ớ,và 
		{//và khác mấy trạng thái có animation

			//DebugOut(L"coooooooooo vooooooo khi an 2 nut cungggggggg songgggg songgggggg\n");
			if (speed_vx <= 0.6 || is_slightly_lower_limit == true)
			{
				vx = (vx + acceleration * dt);// nx;
				//DebugOut(L"co vo doan acceleration maaaaaaaaaaaaaaaaa\n");
				is_max_speed = false;
			}
			else
				is_max_speed = true;

			if (is_max_speed == true)
				is_run_for_fly_high = true;
			//
					//if (vx >= 0)nx = 1;
				//	else  nx = -1;//if(vx<0)

		}
		else if (state != MARIO_STATE_IDLE && state != MARIO_STATE_SPIN && state != MARIO_STATE_FLY && state != MARIO_STATE_FLY_HIGH
			&& state != MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT && state != MARIO_STATE_SPIN && state != MARIO_STATE_SHOOT_BULLET
			&& state != MARIO_STATE_JUMP_SHOOT_BULLET)// ủa tại sao mình lại dùng && ta :v
		{
			if (speed_vx <= 0.32 || is_slightly_lower_limit == true)
			{
				vx = (vx + acceleration * dt);// nx;
				//DebugOut(L"co vo doan acceleration maaaaaaaaaaaaaaaaa\n");
				is_max_speed = false;
			}
			else
				is_max_speed = true;
		}

		//chạy nhanh để cất cánh bay


		DebugOutTitle(L"04 - collision %0.1f, %0.1f", this->x, this->y);


		//phải gia tốc hướng tâm, để có hiệu ứng chầm chầm
		if (is_fly == true)//còn render
		{
			if (GetState() == MARIO_STATE_FLY)// nếu là con cáo bay và ani quẫy đuôi chưa xong
			{
				//if (!animations[MARIO_ANI_TAIL_FLY]->IsRenderDone())
				if (!animation_set->at(MARIO_ANI_TAIL_FLY)->IsRenderDone())
				{
					vy = 0.1;
					//DebugOut(L"Heloo có vô cái bayyyyyy bayyyyy đây hem dạ, vy lúc này là 0.1\n");
				}
			}
			else if (GetState() == MARIO_STATE_FLY_HIGH)
			{
				if (!animation_set->at(MARIO_ANI_TAIL_FLY_HIGH)->IsRenderDone())
					vy = -0.3;
				//DebugOut(L"Heloo có vô cái bayyyyyy bayyyyy đây hem dạ, vy lúc này là 0.1\n");
			}



			/*	if (!(GetState() == MARIO_STATE_FLY_HIGH && animations[MARIO_ANI_TAIL_FLY_HIGH]->IsRenderDone()))//nếu là con cáo bay cao và ani nằm quẫy  chưa xong
				{
					vy = -0.1;
					DebugOut(L"Heloo có vô cái bayyyyyy bayyyyy đây hem dạ, vy lúc này là 0.1\n");
				}*/
		}
		else
		{
			vy += MARIO_GRAVITY * dt;
			//	if(is_run_for_fly_high==true)
				//	is_run_for_fly_high = false;//đang bay cao lên mà rớt xuống rồi thì hông bay lên cao được được, chỉ rơi xuống hoặc rơi xuống nhẹ.
		}


		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear(); // ủa tại sao ở dưới delete rồi mà ở đây lại clear nữa?

		// turn off collision when die 
		if (state != MARIO_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);
		// tính ra danh sách các đối tượng có khả năng va chạm với mario


		// reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		if (GetTickCount() - jumping_start < 250) //  < ấn nhẹ thì nó bay thấp, ấn mạnh thì nó bay cao.
		{											// > ấn nhẹ nhảy cao , ấn mạnh nhảy thấp.
			vy -= MARIO_VY_JUM_UP;
			//DebugOut(L"[ERROR-----------get-------------------] DINPUT::GetDeviceData failed. Error: %lu\n", GetTickCount());
		}

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

			x_flatform = min_tx * dx + nx * 0.4f;
			y_flatform = min_ty * dy + ny * 0.4f;

			vy_flatform = vy;
			vx_flatform = vx;


			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0; // tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
			if (ny != 0) vy = 0; // sẽ bị chặn lại_ không đúng má ơi.

			// Collision logic with Goombas
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{


				//DebugOut(L"[EEEEEEEEEEEEEEE] DINPUT::GetDeviceData failed. Error: %d\n", coEventsResult.size());
				LPCOLLISIONEVENT e = coEventsResult[i];


				if (ny < 0)
				{
					is_in_object = true;
				}

				if (dynamic_cast<CConCo*>(e->obj))
				{
					//DebugOut(L"chạm mấy lần? %d\n");
					CConCo* conco = dynamic_cast<CConCo*>(e->obj);


					if (conco->GetState() == CONCO_STATE_THUT_VAO && is_press_h == true)
					{
						this->hold_somthing = conco;
					}
					else if (conco->GetState() == CONCO_STATE_THUT_VAO && (GetState() == MARIO_STATE_WALKING_RIGHT || GetState() == MARIO_STATE_WALKING_LEFT))
					{
						if (this->x < conco->x)
							conco->SetState(CONCO_STATE_MAI_RUA_CHAY_PHAI);
						else
							conco->SetState(CONCO_STATE_MAI_RUA_CHAY_TRAI);

						SetState(MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT);
					}

					else if (e->ny < 0)
					{
						if (conco->GetState() == CONCO_STATE_THUT_VAO)
							conco->SetState(CONCO_STATE_MAI_RUA_CHAY_PHAI);
						else if (conco->GetState() == CONCO_STATE_WALKING_LEFT || conco->GetState() == CONCO_STATE_WALKING_RIGHT)
						{
							conco->SetState(CONCO_STATE_THUT_VAO);
						}
						else if (conco->GetState() == CONCO_STATE_FLY_LEFT)
							conco->SetState(CONCO_STATE_WALKING_LEFT);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}



					if (state == MARIO_STATE_SPIN)
					{
						//if (goomba->x - this->x < 80);
						conco->SetState(CONCO_STATE_WAS_SHOOTED);
					}




				}
				if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba // nếu như là goomba
				{

					CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->ny < 0) //nêu như phương va chạm hướng lên ( lưu ý trục y hướng xuống)
						// thì cho phép đạp bẹp
					{

						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;

					}

					//SÀI NHA
				//	else if (e->nx != 0) // vec tơ pháp tuyến từ bên trái qua, từ bên phải xuống
				//	{		// thì làm mario rớt level, bất tử hoặc chết
						//if (untouchable==0)
						//{
						//	if (goomba->GetState()!=GOOMBA_STATE_DIE)
						//	{
						//		if (level > MARIO_LEVEL_SMALL)
						//		{
						//			level = MARIO_LEVEL_SMALL;
						//			StartUntouchable();
						//		}
						//		else
						//			SetState(MARIO_STATE_DIE);
						//	}
						//}
						//}

					if (state == MARIO_STATE_SPIN)
					{
						//if (goomba->x - this->x < 80);
						goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);
					}
				}
				if (dynamic_cast<ParaGoomba*>(e->obj))
				{
					ParaGoomba* paragoomba = dynamic_cast<ParaGoomba*>(e->obj);
					if (e->ny < 0) // phương va chạm hướng lên
					{

						if (paragoomba->GetState() == PARA_GROOMBA_STATE_WALKING)
						{
							paragoomba->SetState(PARA_GROOMBA_STATE_DIE);
							//paragoomba->used = true;
							//DebugOut(L"[ERROR-------------para die?----------------] DINPUT::GetDeviceData failed. Error: %f\n", vx);
						}
						else
							paragoomba->SetState(PARA_GROOMBA_STATE_WALKING);

						vy = -MARIO_JUMP_DEFLECT_SPEED;

					}
				}

				if (dynamic_cast<Brick_Coin*>(e->obj))
				{
					Brick_Coin* brickcoin = dynamic_cast<Brick_Coin*>(e->obj);
					if (e->ny > 0) // phương va chạm hướng lên
					{
						if (brickcoin->GetState() == BRICK_COIN_STATE_CHUA_DAP)
						{
							brickcoin->SetState(BRICK_COIN_STATE_DA_DAP);
							brickcoin->is_hit = true;
						}
					}
				}
				if (dynamic_cast<BrickBlink*>(e->obj))
				{
					BrickBlink* brick_blink = dynamic_cast<BrickBlink*>(e->obj);

					if (brick_blink->is_brick == true)
					{
						if (e->ny > 0) // phương va chạm hướng lên
						{
							brick_blink->SetState(BRICK_BLINK_STATE_WAS_HIT);
							//brick_blink->used = true;
						}
					}
					else if (brick_blink->is_brick == false)
					{
						y += (y_flatform + y_flatform);// double for safe
						x += (x_flatform + x_flatform);
						vy = vy_flatform;
						vx = vx_flatform;

						brick_blink->used = true;
					}
				}
				
				//if (dynamic_cast<Flatform*>(e->obj))
				//{
					//is_in_portal = true;
				//}
				

				if (dynamic_cast<Flatform*>(e->obj))
				{
					Flatform* flatform = dynamic_cast<Flatform*>(e->obj);

					if (e->ny < 0 && flatform->is_portal)
					{
						//this->SetPosition(6363 + 16, 1521);
					
						//this->is_on_the_ground = true;

					}
					else if (e->ny > 0 && flatform->is_portal) // hướng xuống
					{
						this->SetPosition(2336 * 3, 360 * 3);
						//CGame::GetInstance()->SetCamPos(2199 * 3 + 16 * 3, 287 * 3 - 150);
						this->is_on_the_ground = false;
					}
					else if (e->ny > 0)
					{
						y += (y_flatform + y_flatform);// double for safe
						vy = vy_flatform;
					}

				}

				if (dynamic_cast<SwitchBlock*>(e->obj))// khỏi bị nhích xuống, rơi ra ngoài thê giưới
				{
					SwitchBlock* switch_block = dynamic_cast<SwitchBlock*>(e->obj);
					if (e->ny < 0) // phương va chạm hướng lên
					{

						switch_block->SetState(SWITCH_BLOCK_STATE_WAS_PRESSED);

					}
				}
		
			}/*
	#pragma region logic collision



				



				

				if (dynamic_cast<Coin*>(e->obj))
				{
					Coin* coin = dynamic_cast<Coin*>(e->obj);
					coin->used = true;

				}

				

	#pragma endregion



			}
		*/
		}

		DebugOut(L"[ERROR------------vx la--------------] DINPUT::GetDeviceData failed. Error: %f\n", vx);

		// clean up collision events

#pragma region Animations Mario

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];



		if (GetState() == MARIO_STATE_SPIN && animation_set->at(39)->IsRenderDone())
		{
			SetState(MARIO_STATE_IDLE);
			SetSpin(false);
			//is_render_animation = false;
		}
		if (GetState() == MARIO_STATE_SHOOT_BULLET && animation_set->at(MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT)->IsRenderDone())
		{
			SetState(MARIO_STATE_IDLE);
			//is_render_animation = false;
		}


		if (GetState() == MARIO_STATE_JUMP_SHOOT_BULLET && animation_set->at(MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT)->IsRenderDone())
		{
			SetState(MARIO_STATE_IDLE);
			//is_render_animation = false;
		}
		if (GetState() == MARIO_STATE_FLY && animation_set->at(MARIO_ANI_TAIL_FLY)->IsRenderDone())
		{
			SetState(MARIO_STATE_IDLE);
			//is_render_animation = false;
			//DebugOut(L"Hello , vo day khong???\n");
			is_fly = false;
			is_fly_short = false;
		}
		if (GetState() == MARIO_STATE_FLY_HIGH && animation_set->at(MARIO_ANI_TAIL_FLY_HIGH)->IsRenderDone())
		{
			SetState(MARIO_STATE_IDLE);
			//is_render_animation = false;
			//DebugOut(L"Hello , vo day khong???\n");
			is_fly = false;
			is_fly_high = false;
		}

		if (is_brouse == true && animation_set->at(MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT)->IsRenderDone())
		{
			SetState(MARIO_STATE_IDLE);
			is_brouse = false;
			//DebugOut(L"Hello vo 700s khong, vo day khong???\n");
			//is_fly = false;
		}

#pragma endregion



		if (this->hold_somthing != NULL)
		{

			this->hold_somthing->SetPosition(this->x + 40, this->y);
			if (this->nx < 0)
				this->hold_somthing->SetPosition(this->x - 40, this->y);

			if (level == MARIO_LEVEL_SMALL)
			{
				this->hold_somthing->SetPosition(this->x + 40, this->y - 50);
				if (this->nx < 0)
					this->hold_somthing->SetPosition(this->x - 40, this->y - 50);
			}

			if (level == MARIO_LEVEL_BIG_TAIL)
			{
				this->hold_somthing->SetPosition(this->x + 50, this->y);
				if (this->nx < 0)
					this->hold_somthing->SetPosition(this->x - 50, this->y);
			}


			CConCo* conco = dynamic_cast<CConCo*>(this->hold_somthing);
			conco->is_brought = true;
			this->is_bring = true;
		}

		//DebugOut(L"[ERROR----vx cua nó la %f\n", vx);

		//DebugOut(L"portalllllllllllllllllllllllllllllll %d\n", is_in_portal);
		//DebugOut(L"UPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPp\n", KeyCode);
	}

	
}

void CMario::Render()
{
	int ani = 0;
	if (state == MARIO_STATE_DIE)
	{
		ani = MARIO_ANI_DIE;
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		if (is_in_object == true)
		{
			if (is_sitdown == false) // trên object thì nó mới sitdown được, if bên ngoài
			{
				//tại vì khi cầm mai con rùa, có lúc va chạm nên vx bằng 0, nó chui vô nên sẽ xẩy
				//ra hiện tượng là cầm mai rùa nhưng vẫn ở rạng thái idle
				if (is_bring == true)
					ani = MARIO_ANI_BRING_KOOMPASHELL_RIGHT;
				else {

					if (is_brouse == true)
						ani = MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT;
					else if (is_max_speed == true && is_press_z == true) //sẽ có trường hợp đang chạy chạy cái thả nút z ra cái nó vẫn chạy, nên thêm is_press vô để xử lí bug đó
						ani = MARIO_ANI_BIG_RUN;
					else if (is_skid == true && is_press_z == true)
						ani = MARIO_ANI_BIG_SKID;
					else if (is_skid == true)
						ani = MARIO_ANI_BIG_SKID;
					else if (state == MARIO_STATE_IDLE)
						ani = MARIO_ANI_BIG_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_WALKING_RIGHT;
				}

			}
			else
				ani = MARIO_ANI_BIG_SITDOWN_RIGT;
		}
		else if (is_in_object == false)
		{
			ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
			if (vy < 0.0f) //fall down
				ani = MARIO_ANI_BIG_JUMP_UP_RIGHT; // mới thêm zô
		}


	}
	else if (level == MARIO_LEVEL_BIG_ORANGE)
	{
		if (is_in_object == true)
		{
			if (is_sitdown == false) // trên object thì nó mới sitdown được, if bên ngoài
			{
				if (state == MARIO_STATE_SHOOT_BULLET)
					ani = MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT;
				else if (is_bring == true)
					ani = MARIO_ANI_ORANGE_BRING_KOOMPASHELL_RIGHT;
				else
				{
					if (is_brouse == true)
						ani = MARIO_ANI_ORANGE_ROUSE_KOOMPASHELL_RIGHT;
					else if (is_max_speed == true && is_press_z == true) //sẽ có trường hợp đang chạy chạy cái thả nút z ra cái nó vẫn chạy, nên thêm is_press vô để xử lí bug đó
						ani = MARIO_ANI_ORANGE_RUN_RIGHT;
					else if (is_skid == true && is_press_z == true)
						ani = MARIO_ANI_ORANGE_SKID_LEFT;
					else if (is_skid == true)
						ani = MARIO_ANI_ORANGE_SKID_LEFT;
					else if (state == MARIO_STATE_IDLE)
						ani = MARIO_ANI_ORANGE_IDLE_RIGHT;
					else
						ani = MARIO_ANI_ORANGE_WALKING_RIGHT;
				}

			}
			else
				ani = MARIO_ANI_ORANGE_SITDOWN_RIGHT;
		}
		else if (is_in_object == false)
		{
			if (state == MARIO_STATE_JUMP_SHOOT_BULLET)
				ani = MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT;
			else
			{
				ani = MARIO_ANI_ORANGE_JUMP_DOWN_RIGHT;
				if (vy < 0.0f)
					ani = MARIO_ANI_ORANGE_JUMP_UP_RIGHT;
			}

		}


	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (is_moving_in_world_map)
			ani = MARIO_ANI_SMALL_IN_MAP;
		else if (is_in_object == true)
		{
			if (is_bring == true)
				ani = MARIO_ANI_SMALL_BRING_KOOMPASHELL_RIGHT;
			else {

				if (is_brouse == true)
					ani = MARIO_ANI_SMALL_ROUSE_KOOMPASHELL_RIGHT;
				else if (is_max_speed == true && is_press_z == true) //sẽ có trường hợp đang chạy chạy cái thả nút z ra cái nó vẫn chạy, nên thêm is_press vô để xử lí bug đó
					ani = MARIO_ANI_SMALL_RUN_RIGHT;
				else if (is_skid == true && is_press_z == true)
					ani = MARIO_ANI_SMALL_SKID_LEFT;
				else if (is_skid == true)
					ani = MARIO_ANI_SMALL_SKID_LEFT;
				else if (state == MARIO_STATE_IDLE)
					ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				else
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
			}



		}
		else if (is_in_object == false)
			//	{
					//if (nx > 0)
					//{
			ani = MARIO_ANI_SMALL_JUMP_RIGHT;
		//}
	//	else if (nx < 0)
		//{
		//	ani = MARIO_ANI_SMALL_JUMP_LEFT;
		//}


//	}

	}
	else if (level == MARIO_LEVEL_BIG_TAIL)
	{
		if (state == MARIO_STATE_SPIN)
			ani = MARIO_ANI_TAIL_SPIN_TAIL_RIGHT;
		else if (is_in_object == false)
		{
			if (is_fly_short)
				ani = MARIO_ANI_TAIL_FLY;
			else if (is_fly_high)
				ani = MARIO_ANI_TAIL_FLY_HIGH;
			else
			{
				ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;



				if (vy < 0.0f)
					ani = MARIO_ANI_TAIL_JUMP_UP_RIGHT;
				// if(vy==0.1)
				//	 ani = MARIO_ANI_FLY;




				// if(is_fly==true)
				//	 ani = MARIO_ANI_TAIL_FLY;
				// if(state== MARIO_STATE_WALKING_RIGHT)
				//	 ani = MARIO_ANI_TAIL_FLY_HIGH;

			}

		}
		else if (is_in_object == true)
		{
			if (state == MARIO_STATE_GO_DOWN_PINE)
				ani = MARIO_ANI_TAIL_GO_DOWN;
			else if (is_sitdown == true) // trên object thì nó mới sitdown được, if bên ngoài
				ani = MARIO_ANI_TAIL_SITDOWN_RIGHT;
			else if (is_bring == true)
				ani = MARIO_ANI_TAIL_BRING_KOOMPASHELL_RIGHT;
			else
			{
				if (is_brouse == true)
					ani = MARIO_ANI_TAIL_ROUSE_KOOMPASHELL_RIGHT;
				else if (is_max_speed == true && is_press_z == true) //sẽ có trường hợp đang chạy chạy cái thả nút z ra cái nó vẫn chạy, nên thêm is_press vô để xử lí bug đó
					ani = MARIO_ANI_TAIL_RUN_RIGHT;
				else if (is_skid == true && is_press_z == true)
					ani = MARIO_ANI_TAIL_SKID_LEFT;
				else if (is_skid == true)
					ani = MARIO_ANI_TAIL_SKID_LEFT;
				else if (state == MARIO_STATE_IDLE)
					ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				else
					ani = MARIO_ANI_TAIL_WALKING_RIGHT;
			}

		}

	}


	for (int i = 0; i < listWeapons.size(); i++)
	{
		listWeapons[i]->Render();
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	//if (ani <= 28 && ani >= 25)
	//	nx = !nx;

	DebugOut(L"[ERROR---------------ani--------------------ani cua nó la %d\n", ani);
	//DebugOut(L"[ERROR---------------nx--------------------ani cua nó la %d\n", nx);
	//DebugOut(L"[ERROR---------------nx--------------------ani cua nó la %f\n", vx);
	//DebugOut(L"[ERROR----state cua nó la %d\n", state);

	if (is_go_down_pine == true)
		ani = MARIO_ANI_TAIL_GO_DOWN;
	animation_set->at(ani)->Render(x, y, 0, alpha, nx);

	RenderBoundingBox();
}

int CMario::hihih()
{
	return 0;
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT://================================================================================
		if (is_press_z == true)
			return;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT://================================================================================ 
		if (is_press_z == true)
			return;
		nx = -1;
		break;
	case MARIO_STATE_GO_DOWN_PINE:
		//vy = -MARIO_JUMP_SPEED_Y;
		vx = 0;
		vy =  0.03;
		break;
	case MARIO_STATE_GO_UP_PINE:
		//vy = -MARIO_JUMP_SPEED_Y;
		vx = 0;
		vy = -0.03;
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;
		break;
	case MARIO_STATE_SITDOWN:
		is_sitdown = true;
		vx = 0;
		break;
	case MARIO_STATE_IDLE:
		is_sitdown = false;
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_MOVE_IN_WORLD_MAP:
		//vy = -MARIO_DIE_DEFLECT_SPEED;
		vx = 0;
		vy = 0;
		break;
	case MARIO_STATE_SPIN:
		animation_set->at(39)->ResetCurrentFrame();
		animation_set->at(39)->StartTimeAnimation();
		//vx = 0;
		break;
	case MARIO_STATE_SHOOT_BULLET:
		animation_set->at(MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT)->ResetCurrentFrame();
		animation_set->at(MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT)->StartTimeAnimation();
		break;
	case MARIO_STATE_JUMP_SHOOT_BULLET:
		animation_set->at(MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT)->ResetCurrentFrame();
		animation_set->at(MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT)->StartTimeAnimation();
		break;
	case MARIO_STATE_FLY:
		animation_set->at(MARIO_ANI_TAIL_FLY)->ResetCurrentFrame();
		animation_set->at(MARIO_ANI_TAIL_FLY)->StartTimeAnimation();
		is_fly_short = true;
		break;
	case MARIO_STATE_FLY_HIGH:
		animation_set->at(MARIO_ANI_TAIL_FLY_HIGH)->ResetCurrentFrame();
		animation_set->at(MARIO_ANI_TAIL_FLY_HIGH)->StartTimeAnimation();
		is_fly_high = true;
		break;
	case MARIO_STATE_BRING_KOOMPASHELL_RIGHT:
		vx = 1.5 * nx;
		break;
	case MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT:
		animation_set->at(MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT)->ResetCurrentFrame();
		animation_set->at(MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT)->StartTimeAnimation();
		is_brouse = true;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//left = x;
	//top = y; 
	left = x - MARIO_BIG_BBOX_WIDTH / 2;
	top = y - MARIO_BIG_BBOX_HEIGHT / 2;
	
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_BIG_ORANGE)
	{
		if (is_sitdown == false) {

			right = x + MARIO_BIG_BBOX_WIDTH / 2;
			bottom = y + MARIO_BIG_BBOX_HEIGHT / 2;
		}
		else
		{
			//left = x - MARIO_BIG_SITDOWN_BBOX_WIDTH / 2;
			//top = y - MARIO_BIG_SITDOWN_BBOX_HEIGHT / 2;
			right = x + MARIO_BIG_SITDOWN_BBOX_WIDTH / 2;
			bottom = y + MARIO_BIG_SITDOWN_BBOX_HEIGHT / 2;
		}

	}
	else if (level == MARIO_LEVEL_BIG_TAIL)
	{
		if (is_sitdown == false)
		{

			right = x + MARIO_BIG_TAIL_BBOX_WIDTH / 2;
			bottom = y + MARIO_BIG_TAIL_BBOX_HEIGHT / 2;

			if (state == MARIO_STATE_SPIN)
			{
				right = x + MARIO_BIG_TAIL_SPIN_BBOX_WIDTH / 2;
				bottom = y + MARIO_BIG_TAIL_BBOX_HEIGHT / 2;
			}
		}
		else
		{
			right = x + MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH / 2;
			bottom = y + MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT / 2;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		//	left = x - MARIO_SMALL_BBOX_WIDTH / 2;
			//top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = x + MARIO_SMALL_BBOX_WIDTH / 2;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT / 2;
	}
}

