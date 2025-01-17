#pragma once
#include<exception>
#include<string>
class AExceptii
{
protected:
	std::string mesaj;
public:
	AExceptii(const std::string& mesaj):
		mesaj(mesaj){}
	const char* what()const noexcept {
		return mesaj.c_str();
	}
	virtual ~AExceptii() = 0;
};

