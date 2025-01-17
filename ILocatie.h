#pragma once
#include<string>
#include<list>
#include<iostream>
class ILocatie
{
public:
	virtual ~ILocatie() = 0;
	virtual std::string getTara()const = 0;
	virtual std::string getNume()const = 0;
	virtual std::string getFilename()const = 0;
	virtual float getRating() = 0;
	virtual void changeRating() = 0;
};

