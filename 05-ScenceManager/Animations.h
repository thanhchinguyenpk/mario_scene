#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "TimerCustom.h"
#include "Sprites.h"

/*
Sprite animation
*/

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;
/*
class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);

	void Render(float x, float y, int offetX = 0, int alpha = 255, int nx = 1, int ny = 1);
};*/

class CAnimation
{
	TimerCustom *timer;
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime=100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	//void CSprite::DrawFlipX(float x, float y, int offsetX, int alpha, int nx)
	void Render(float x, float y, int offetX = 0, int alpha = 255, int nx = 1, int ny = 1);
	void ResetCurrentFrame() { currentFrame = -1; };
	void StartTimeAnimation();
	bool IsRenderDone();


};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();

	static CAnimations * GetInstance();
};


/*
* giúp mình trong trường hợp có nhiều đối tượng mà nó	chia sẻ một cái animationtest, thay vì chúng ta
* lưu một vector thì mình chỉ cần lưu một con trỏ đến texture thôi là xong
*/
typedef vector<LPANIMATION> CAnimationSet;
/* lý do define như vầy để mà trong trường hợp sau này muốn mở rộng khái niệm của animation set này bổ
sung thêm thuộc tính gì phức tạp vô á , mình mình có thể biến nó thành cái lớp, thì làm cho mình khong
phỉa sửa cái code sử dụng animation set này quá nhiều*/
typedef CAnimationSet* LPANIMATION_SET; // là một vector chứa các animation

/*
	Manage animation set database
*/
/* tương tự như vậy thì mình có một database lưu tất cả các animationset này*/


class CAnimationSets
{
	static CAnimationSets * __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);


	static CAnimationSets * GetInstance();
};