#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom);
}

void CSprite::DrawFlipXX(float x, float y, int offsetX, int alpha, int nx)
{

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	float cam_x, cam_y;
	cam_x = 0;
	cam_y = 0;

	// tọa độ của sprite trên màn hình
	D3DXVECTOR3 p(floor(x - cam_x), floor(y - cam_y), 0);

	// tọa độ của sprite trong texture
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	// dùng ma trận middleTransform để tính ra các thông số transform
	// dùng ma trận newTransform để lưu lại ma trận sau khi tính -  tức là tile sau khi đã scale bự lên
	// dùng ma trận oldTransform để lưu lại tile 16x16
	D3DXMATRIX oldTransform, middleTransform;
	spriteHandler->GetTransform(&oldTransform);

	/*
	&D3DXVECTOR2(p.x , p.y): vị trí xoay sprite, với giá trị bằng đúng position thì xoay quanh tâm
	&D3DXVECTOR2(scale, scale): phóng đại theo hai chiều x, y nếu âm là lật frame ngược lại
	các thông số còn lại dùng cho việc xoay góc bao nhiêu độ,... ở đây vẽ tile không cần
	*/
	D3DXMatrixTransformation2D(&middleTransform, &D3DXVECTOR2(p.x + offsetX, p.y), 0,
		&D3DXVECTOR2(3.0f * nx, 3.0f), NULL, 0.0f, NULL);

	D3DXMATRIX newTransform = oldTransform * middleTransform;
	spriteHandler->SetTransform(&newTransform);
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldTransform);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}
//void CSprite::DrawFlipX(float x, float y, int offsetX, int alpha, int nx)
void CAnimation::Render(float x, float y,int offsetX,int aplpha,int nx)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}
		
	}
	if (nx > 0)
		offsetX = 0;
	else
		offsetX = 13;
	frames[currentFrame]->GetSprite()->DrawFlipXX(x, y, offsetX,255,nx);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}