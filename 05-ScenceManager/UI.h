#pragma once
#include "TextAndNumber.h"
#include "Game.h"
class UI
{

	float posX=100, posY=800;
	
	TextAndNumber text;
public:

	UI() {};
	~UI() {};

	void Update();
	void Render(int remainingTim);
};

