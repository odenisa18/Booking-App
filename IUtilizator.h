#pragma once
#include<string>
#include<list>
#include<iostream>
#include"PortofelElectronic.h"
#include"CPlanificator.h"
class IUtilizator
{
public:
	virtual ~IUtilizator()=0;
	virtual void printInfoUtilizator()const =0;
	virtual std::string getNume() = 0;
	virtual std::string getParola() = 0;
};

