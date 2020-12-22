#pragma once

#include "Sprites.h"
#include <string>

class TextAndNumber
{
	LPSPRITE textSpr;

	public:
		void Render(float posX, float posY, const string& str);
		string FillZeroString(string str, UINT MaxStringLenght);

		TextAndNumber() {};
		~TextAndNumber() {};

};

