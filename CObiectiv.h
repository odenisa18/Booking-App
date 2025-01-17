#pragma once
#include "ALocatie.h"
class CObiectiv :public ALocatie
{
private:
	std::string categorie;
	std::string descriere;
	std::string program;
	std::string durata;//in ore/minute
	std::list<std::string>categorieBiletSiPret;
public:
	CObiectiv(const std::string& tara, const std::string& denumire, float rating, const std::string& filename, const std::string&categorie,const std::string& descriere,const std::string& program,const std::string &durata):
		ALocatie(tara, denumire, rating,filename),categorie(categorie),descriere(descriere),program(program),durata(durata){}
	void addCategorieBiletSiPret(const std::string& priceandCategory) {
		categorieBiletSiPret.push_back(priceandCategory);
	}
	void printObiectivTuristic()const {
		std::cout << "\n\t\t\tObiectiv Turistic : " << denumire;
		std::cout << "\n~Tara:" << tara;
		std::cout << "\n*Rating:" << rating;
		std::cout << "\nCategorie:" << categorie;
		std::cout << "\nDescriere si informatii cheie:" << descriere;
		std::cout << "\nProgram:" << program;
		std::cout << "\nDurata recomandata pentru vizita completa:" << durata;
		std::cout << "\nPret si Tip Bilet de Acces:";
		printCategorieSiPretBilet();
	}
	void printCategorieSiPretBilet()const {
		if (categorieBiletSiPret.size() == 0) {
			std::cout << "\nObiectivul de vizitare este gratuit.";
		}
		else {
			for (auto& i : categorieBiletSiPret)
			{
				std::cout << "\n" << i; ;
			}
		}
	}
	std::string getDescriere()
	{
		return descriere;
	}
	std::string getProgram()
	{
		return program;
	}
	std::string getDurata()
	{
		return durata;
	}
	std::list<std::string>getCategoriiBilete() {
		return categorieBiletSiPret;
	}
	std::string getCategorie() {
		return categorie;
	}
	~CObiectiv()override {

	}
};

