#pragma once
#include "ILocatie.h"
class ALocatie :public ILocatie
{
protected:
	std::string tara;
	std::string denumire;
	float rating;
	std::list<std::string>oraseVecine;
	std::string filename;
public:
	ALocatie(const std::string& tara,const std::string& denumire,float rating, const std::string&filename):
		tara(tara),denumire(denumire),rating(rating),filename(filename){}
	void addOrasVecin(const std::string& oras) {
		oraseVecine.push_back(oras);
	}
	std::string getTara()const override {
		return tara;
	}
	std::string getFilename()const override {
		return filename;
	}
	float getRating()override
	{
		return rating;
	}
	std::string getNume()const override{
		return denumire;
	}
	void changeRating()override
	{
		std::cout << "\nIntrodu nota pe care doresti sa o acorzi (1-5) :";
		float nota;
		std::cin >> nota;
		rating = ((rating * 1) + nota) / (1 + 1);
		std::cout << "\nRating"<<rating;
	}
	virtual ~ALocatie() = 0;
};

