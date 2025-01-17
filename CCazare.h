#pragma once
#include "ALocatie.h"
#include<utility>
class CCazare :public ALocatie
{
private:
	std::string clasificare;
	int nrCamere;
	bool admisAnimal;
	std::list<std::pair<std::string,float>>tipCamereSiPret;
	std::list<std::string>perioadeLibere;
	std::list<std::string>perioadeAglomerate;
public:
	CCazare(const std::string& tara, const std::string& denumire, float rating, const std::string& filename, const std::string& clasificare, int nrCamere, bool admisAnimal) :
		ALocatie(tara, denumire, rating,filename), clasificare(clasificare), nrCamere(nrCamere), admisAnimal(admisAnimal) {}
	void addTipCamera(const std::string& type,float price) {
		tipCamereSiPret.push_back(std::make_pair(type, price));
	}
	void addPerioadaLibera(const std::string&perLibera) {
		perioadeLibere.push_back(perLibera);
	}
	void addPerioadaAglomerata(const std::string&perAglomerata) {
		perioadeAglomerate.push_back(perAglomerata);
	}
	void printPerioadeAglomerate()const  {
		std::cout << "\n~Perioade aglomerate Hotel:";
		for (auto& b : perioadeAglomerate)
		{
			std::cout << "\n\t" << b;
		}
	}
	void printPerioadeLibere()const {
		std::cout << "\n~Perioade libere Hotel:";
		for (auto& c : perioadeLibere)
		{
			std::cout << "\n\t" << c;
		}
	}
	void printCazare()const {
		std::cout << "\n\t\t\tCazare : " << denumire;
		std::cout << "\n~Tara:" << tara;
		std::cout << "\n~Clasificare:" << clasificare;
		std::cout << "\n*Rating:" << rating;
		std::cout << "\n~Animal de companie:" << (admisAnimal ?  "Permise": "Interzise");
		std::cout << "\n~Numar de camere:" << nrCamere;
		std::cout << "\n~Tipuri de camere:";
		for (auto& a : tipCamereSiPret)
		{
			std::cout <<"\n\t" <<a.first << "-" << a.second << "lei/noapte.";
		}
		printPerioadeAglomerate();
		printPerioadeLibere();
	}

	void printTipuriCamere()const 
	{
		std::cout << "\nCamere disponibile:";
		for (auto& i : tipCamereSiPret) {
			std::cout <<"\n" << i.first << " - " << i.second;
		}
	}
	const std::string getClasificare() {
		return clasificare;
	}
	bool getTipCamera(std::list<std::string>tipuri,int sizeTipuri) {
		int nr = 0;

		for (auto& i : tipCamereSiPret)
		{
			for (auto& j : tipuri) {
				if (i.first == j) {
					nr++;
				}
			}
		}
		if (nr == sizeTipuri)return true;
		return false;
	}
	float getPretCamera(const std::string& type) {
		for (auto& i : tipCamereSiPret)
		{
			if (i.first == type) {
				return i.second;
			}
		}
	}
	const std::string getadmisAnimal() {
		if (admisAnimal) {
			return "CU";
		}
		return "FARA";
	}
	std::string searchPerioadaLibera(const std::list<std::string> perioada) {
		
		//caut printre perioadele libere
		for (auto&i: perioadeLibere)
		{
			//plec de la premiza ca nu am gasit una din datele preferate ca fiind libera
			bool found = false;
			for (auto& p : perioada)
			{
				if (p == i)found = true;
				//daca gasec marchez ca gasit
			}
			if (found == false)
			{
				//daca nu am gasit una din date ca fiind valabila returnez ca vacanta nu poate fi planificata la acest hotel
				return "Invalid";
			}
		}
		return "Valid";
	}
	~CCazare()override {

	}
};