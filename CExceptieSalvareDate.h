#pragma once
#include "AExceptii.h"
class CExceptieSalvareDate :public AExceptii
{
public:
	CExceptieSalvareDate(std::string mesaj) :
		AExceptii(mesaj) {}
	~CExceptieSalvareDate()override {

	}
};

