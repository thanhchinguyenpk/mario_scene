#pragma once
#include "GameObject.h"

#define	 PINE_TALL_BBOX_WIDTH 32*3
#define	 PINE_TALL_BBOX_HEIGHT 48*3

#define	 PINE_SHORT_BBOX_WIDTH 32*3
#define	 PINE_SHORT_BBOX_HEIGHT 32*3

#define  PARA_GROOMBA_WALKING_SPEED			 0.03f;

#define  PINE_STATE_TALL				100
#define  PINE_STATE_SHORT				200
#define  PINE_STATE_BLACK				300

#define	 PARA_GROOMBA_SPEED_VERTICAL		0.1


#define  PARA_GROOMBA_GRAVITY		0.0009

class Pine : public CGameObject
{
public:
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
};
