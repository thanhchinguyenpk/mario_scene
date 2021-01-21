#pragma once
#include "GameObject.h"
#include "MarioBullet.h"


#define MARIO_WALKING_SPEED			0.3 
#define MARIO_JUMP_SPEED_Y			0.66
#define MARIO_JUMP_DEFLECT_SPEED	0.72
#define MARIO_GRAVITY				0.003
#define MARIO_DIE_DEFLECT_SPEED	 1.5
#define MARIO_ACCELERATION		 0.0005
#define MARIO_VY_JUM_UP			 0.04

#define MARIO_STATE_IDLE						0
#define MARIO_STATE_WALKING_RIGHT				100
#define MARIO_STATE_WALKING_LEFT				200
#define MARIO_STATE_JUMP						300
#define MARIO_STATE_DIE							400
#define MARIO_STATE_SITDOWN						500
#define MARIO_STATE_SHOOT_BULLET				600
#define MARIO_STATE_SPIN						700
#define MARIO_STATE_JUMP_SHOOT_BULLET			800
#define MARIO_STATE_FLY							900
#define MARIO_STATE_FLY_HIGH					1000
#define MARIO_STATE_BRING_KOOMPASHELL_RIGHT			1100
#define MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT			1200
#define MARIO_STATE_MOVE_IN_WORLD_MAP			1300
#define MARIO_STATE_GO_DOWN_PINE			1400
#define MARIO_STATE_GO_UP_PINE			1500
#define MARIO_STATE_TRANSFORM		1600
#define MARIO_STATE_APPEAR_TAIL		1700

#define MARIO_ANI_BIG_IDLE_RIGHT			0
#define MARIO_ANI_SMALL_IDLE_RIGHT			1
#define MARIO_ANI_TAIL_IDLE_RIGHT			2 
#define MARIO_ANI_ORANGE_IDLE_RIGHT			3 


#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define	MARIO_ANI_SMALL_WALKING_RIGHT		5
#define MARIO_ANI_TAIL_WALKING_RIGHT		6
#define MARIO_ANI_ORANGE_WALKING_RIGHT		7


#define MARIO_ANI_DIE				8

#define MARIO_ANI_BIG_JUMP_UP_RIGHT				9
#define MARIO_ANI_SMALL_JUMP_RIGHT				10
#define MARIO_ANI_TAIL_JUMP_UP_RIGHT			11
#define MARIO_ANI_ORANGE_JUMP_UP_RIGHT			12

#define MARIO_ANI_BIG_SITDOWN_RIGT			13
#define MARIO_ANI_TAIL_SITDOWN_RIGHT		14
#define MARIO_ANI_ORANGE_SITDOWN_RIGHT		15



#define MARIO_ANI_SMALL_JUMP_DOWN_RIGHT				16
#define MARIO_ANI_BIG_JUMP_DOWN_RIGHT				17
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT				18
#define MARIO_ANI_ORANGE_JUMP_DOWN_RIGHT			19


#define	MARIO_ANI_SMALL_RUN_RIGHT			        20
#define	MARIO_ANI_BIG_RUN							21
#define	MARIO_ANI_TAIL_RUN_RIGHT					22
#define MARIO_ANI_ORANGE_RUN_RIGHT					23

#define  MARIO_ANI_TAIL_SPIN_TAIL_RIGHT			24


#define  MARIO_ANI_BIG_SKID				25
#define  MARIO_ANI_TAIL_SKID_LEFT		26
#define  MARIO_ANI_SMALL_SKID_LEFT		27
#define  MARIO_ANI_ORANGE_SKID_LEFT		28

#define MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT			29

#define MARIO_ANI_SMALL_FLYING								30
#define MARIO_ANI_BIG_FLYING								31
#define MARIO_ANI_TAIL_FLY_HIGH									32
#define MARIO_ANI_ORANGE_FLYING								33
#define MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT			34


#define MARIO_ANI_SMALL_BRING_KOOMPASHELL_RIGHT	 		35
#define MARIO_ANI_BRING_KOOMPASHELL_RIGHT				36
#define MARIO_ANI_TAIL_BRING_KOOMPASHELL_RIGHT			37
#define MARIO_ANI_ORANGE_BRING_KOOMPASHELL_RIGHT		38

#define	MARIO_ANI_SMALL_ROUSE_KOOMPASHELL_RIGHT		39
#define MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT			40
#define MARIO_ANI_TAIL_ROUSE_KOOMPASHELL_RIGHT		41
#define MARIO_ANI_ORANGE_ROUSE_KOOMPASHELL_RIGHT	42

#define MARIO_ANI_SMALL_STAND_HOLD  43
#define MARIO_ANI_BIG_STAND_HOLD    44
#define MARIO_ANI_TAIL_STAND_HOLD   45
#define MARIO_ANI_ORANGE_STAND_HOLD 46

#define MARIO_ANI_SMALL_GROW_UP			47
#define MARIO_ANI_BIG_GROW_UP			48

#define MARIO_ANI_SMALL_GO_DOWN			49
#define MARIO_ANI_BIG_GO_DOWN			50
#define MARIO_ANI_TAIL_GO_DOWN			51
#define MARIO_ANI_ORANGE_GO_DOWN		52

#define MARIO_ANI_SMALL_IN_MAP			53
#define MARIO_ANI_BIG_IN_MAP			54
#define MARIO_ANI_TAIL_IN_MAP			55
#define MARIO_ANI_ORANGE_IN_MAP			56



//nhớ còn ani này nha 
#define MARIO_ANI_TAIL_FLY								57 //need

#define MARIO_ANI_TRANSFORM			58
#define MARIO_ANI_APPEAR_TAIL			59



#define	MARIO_LEVEL_SMALL			1
#define	MARIO_LEVEL_BIG				2
#define	MARIO_LEVEL_BIG_TAIL		3
#define	MARIO_LEVEL_BIG_ORANGE		4

#define MARIO_BIG_BBOX_WIDTH  15*3
#define MARIO_BIG_BBOX_HEIGHT 27*3

#define MARIO_BIG_SITDOWN_BBOX_WIDTH  14*3
#define MARIO_BIG_SITDOWN_BBOX_HEIGHT 19*3

#define MARIO_SMALL_BBOX_WIDTH  13*3
#define MARIO_SMALL_BBOX_HEIGHT 15*3

#define MARIO_BIG_TAIL_BBOX_WIDTH  21*3
#define MARIO_BIG_TAIL_BBOX_HEIGHT 28*3

#define MARIO_BIG_TAIL_SPIN_BBOX_WIDTH  45*3


#define MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH  22*3
#define MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT 19*3




#define MARIO_UNTOUCHABLE_TIME 2000



class CMario : public CGameObject
{
public:

	int score = 0;
	int number_brick_coin_hit = 0;
	vector <int> cards;

	bool is_die = false;
	int level;
	int untouchable;
	float acceleration= MARIO_ACCELERATION;
	CGameObject* hold_somthing = NULL;

	bool is_hit_bonus = false;
	bool is_auto_running = false;

	DWORD untouchable_start;
	DWORD jumping_start;

	


	DWORD time_to_transform_start = 0;
	DWORD time_to_appear_tail = 0;
	DWORD time_to_die = 0;




	DWORD fly_start=0;
	DWORD fly_high_start = 0;
	DWORD fly_fire_throw_start = 0;
	DWORD spin_start = 0;
	DWORD throw_start = 0;
	DWORD rouse_start = 0;
	
	vector<LPGAMEOBJECT> listWeapons;

	bool is_go_down_pine = false;
	DWORD go_down_pine_then_move_cam = 0;
	bool is_in_portal = false;

	bool is_in_end_scene = false; 
	bool is_in_near_end_scene = false;

	bool is_moving_in_world_map = false;
	bool is_on_the_ground = false;

	bool is_in_object = false;
	bool is_sitdown = false;
	bool is_shoot = false;
	bool is_spin = false;
	bool is_slightly_lower_limit = false; // đã đến lúc giảm tốc
	bool is_right = false;
	bool is_left = false;
	bool is_skid = false;
	bool is_max_speed = false;
	bool is_walking = false;
	bool is_press_z = false;
	bool is_slightly_lower_than_zero = false;
	bool is_press_left = false;
	bool is_brouse = false;
	bool is_press_h = false;
	bool is_fly = false;
	bool is_fly_short = false;
	bool is_fly_high = false;
	bool is_bring = false;
	bool is_increase_speed = false;
	bool is_run_for_fly_high = false;

public: 
	CMario() : CGameObject()
	{
		level = MARIO_LEVEL_SMALL;
		is_moving_in_world_map = true;
		SetState(MARIO_STATE_MOVE_IN_WORLD_MAP);

		untouchable = 0;
		nx = 1;
	}
	
	void CheckOverlapWithItems(vector<LPGAMEOBJECT>* itemsMarioCanEat);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void Attack();
	

	void SetState(int state);
	int hihih();
	void SetIsInObject(bool temp) { is_in_object = temp; }
	void SetLevel(int l) { level = l; y = y - 20; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void SetShoot(bool temp) { is_shoot = temp; }
	void SetSpin(bool temp) { is_spin = temp; }
	void SetIsFly(bool temp) { is_fly = temp; }
	void SetIsBring(bool temp) { is_bring = temp; }
	void SetIsIncreaseSpeed(bool temp) { is_increase_speed = temp; }
	void SetAcceleration(float temp) { acceleration = temp; }

	void StartJumping() { jumping_start = GetTickCount64(); };
	void EndJumping() { jumping_start = 0; };
	DWORD GetJumpingTime() { return jumping_start; };
	bool GetIsInObject() { return is_in_object; };
	int GetLevel() { return level; };
	bool GetIsShoot() { return is_shoot; };
	bool GetIsSpin() { return is_spin; };
	bool GetIsFly() { return is_fly; };
	bool GetIsBring() { return is_bring; };
	bool GetIsIncreaseSpeed() { return is_increase_speed; }
	float GetAcceleration() { return acceleration; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void CollideWithEnemy();

	int distance_to_set_state_enemy = 600;
};