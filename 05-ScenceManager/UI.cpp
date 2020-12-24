#include "UI.h"

void UI::Update()
{

}

void UI::Render(int remainingTime,int the_number_mario_hit_brick, int point_hub,int id_map,int world )
{
	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();
	text.Render(x+405, y+658, to_string(remainingTime));

	text.Render(x + 190, y + 658, text.FillZeroString(to_string(point_hub),7));

	text.Render(x + 453, y + 635, to_string(the_number_mario_hit_brick));

	text.Render(x + 140, y + 635, to_string(world));
	text.Render(x + 140, y + 658, to_string(id_map));

	

}
