#pragma once
#include"AExceptii.h"
class CExceptieCreareLocatie :public AExceptii
{
public:
	CExceptieCreareLocatie(std::string mesaj) :
		AExceptii(mesaj){}
	~CExceptieCreareLocatie()override {

	}
};

