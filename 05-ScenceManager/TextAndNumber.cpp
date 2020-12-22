#include "TextAndNumber.h"

void TextAndNumber::Render(float posX, float posY, const string& str)
{
	for (UINT i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			textSpr = CSprites::GetInstance()->Get(str[i] - '0' + 200000);
		//else
			//textSpr=CSprites::GetInstance()->Get()

		textSpr->DrawFlipX(posX + i * 24, posY );
	}

}
