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
	void Render(int remainingTime, int the_number_mario_hit_brick, int point_hub, int id_map, int world);
};

