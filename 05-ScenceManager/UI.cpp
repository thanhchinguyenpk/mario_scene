#include "UI.h"

void UI::Render(int remainingTime)
{
	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();
	text.Render(x+405, y+658, to_string(remainingTime));
}
