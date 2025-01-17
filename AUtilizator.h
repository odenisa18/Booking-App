#pragma once
#include "IUtilizator.h"
class AUtilizator :public IUtilizator
{
protected:
	std::string nume;
	std::string parola;
public:
	AUtilizator(const std::string& nume,const std::string& parola) :
		nume(nume), parola(parola){}
	virtual void printInfoUtilizator()const = 0;
	std::string getNume()override {
		return nume;
	}
	std::string getParola() override {
		return parola;
	}
	virtual ~AUtilizator() = 0;
};

