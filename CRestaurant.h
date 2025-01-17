#pragma once
#include "ALocatie.h"
class CRestaurant :public ALocatie
{
private:
	std::string tipBucatarie;
	std::string meniu;
	float pretMediu;
	bool meniuCopil;
	bool ales=false;
public:
	CRestaurant(const std::string& tara, const std::string& denumire, float rating, const std::string& filename, const std::string& tipBucatarie, const std::string& meniu, float pretMediu, bool meniuCopil) :
		ALocatie(tara, denumire, rating,filename), tipBucatarie(tipBucatarie), meniu(meniu), pretMediu(pretMediu), meniuCopil(meniuCopil){}
	void printRestaurant()const {
		std::cout << "\n\t\t\tRestaurant : " << denumire;
		std::cout << "\n~Tara:" << tara;
		std::cout << "\n*Rating:" << rating;
		std::cout << "\nTip Bucatarie:" << tipBucatarie;
		std::cout << "\nMeniu" << meniu;
		std::cout << "\nPretul mediu/persoana este:" << pretMediu;
		std::cout << "\nDetine meniu de copil:" << (meniuCopil ? "DA" : "NU");
	}
	std::string getTypeKitchen() {
		return tipBucatarie;
	}
	float getPriceMediu()
	{
		return pretMediu;
	}
	void setAles() {
		ales = true;
	}
	bool getAles()
	{
		return ales;
	}
	bool hasmeniuCopil() {
		return meniuCopil;
	}
	std::string getMeniu()
	{
		return meniu;
	}
	~CRestaurant()override {

	}
};

