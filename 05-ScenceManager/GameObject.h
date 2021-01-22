#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	int w;
	int h;
	int id_grid;

	bool is_cam_coming = false;

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx = 1;
	int ny = 1;

	int state;
	bool used = false;
	DWORD dt; 

	LPANIMATION_SET animation_set;
	/*thay vì chứa nguyên một cái vector gồm danh sách các animation mình set ngay lúc đầu thì
	đơn giản mình chỉ chứa con trỏ đến nguyên một cái animationset
	như thế nào là một animationset? animation set là bao gồm hết tất cả các animation của nhân vật đó luôn
	.Chẳng hạn như đối với mario thì bao gồm cả animation đi qua bên trái, đi qua bên phải, lên trên
	rồi nhảy,...nhỏ lớn gì là phải có hết
	nó sẽ giúp tiết kiệm, thay vì phải lưu một vector trong một object, nó giúp mình khởi tạo tốt hơn,
	nhanh hơn.
	khuyết: nhiều đối tượng chia sẽ một animationset, thì các con đó giống như là đồng bộ với nhau.

	*/
public: 
	void DeleteWhenOutOfCam();
	bool CheckOverLap(float l_a, float t_a, float r_a, float b_a, float l_b, float t_b, float r_b, float b_b) { return (l_a < r_b && r_a > l_b && t_a < b_b && b_a > t_b); }

	float GetX() { return this->x; }
	float GetY() { return this->y; }
	int GetNX() { return this->nx; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);
	//&rdx;
	//&rdy;
	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};

