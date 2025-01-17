#pragma once
#include "AExceptii.h"
class CExceptieDeschidereFisierContent :public AExceptii
{
private:
	std::string mesaj;
public:
	CExceptieDeschidereFisierContent(std::string mesaj) :
		AExceptii(mesaj){}

	~CExceptieDeschidereFisierContent()override{
	}
};

