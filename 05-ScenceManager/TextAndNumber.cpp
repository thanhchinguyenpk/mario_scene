#include "TextAndNumber.h"

void TextAndNumber::Render(float posX, float posY, const string& str)
{
	for (UINT i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			textSpr = CSprites::GetInstance()->Get(str[i] - '0' + 200000);
		else if(str[i] >= 'A' && str[i] <= 'Z')
			textSpr = CSprites::GetInstance()->Get(str[i] - 'A' + 200010);
		else if(str[i] == '!')
			textSpr = CSprites::GetInstance()->Get(200036);
		else if(str[i] == ' ')
			textSpr = CSprites::GetInstance()->Get(200037);
		//else
			//textSpr=CSprites::GetInstance()->Get()

		textSpr->DrawFlipX(posX + i * 24, posY );
	}

}

string TextAndNumber::FillZeroString(string str, int MaxStringLenght)
{
	while (str.size() < MaxStringLenght)
		str = "0" + str;
	return str;
}
