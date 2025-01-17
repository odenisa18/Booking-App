#pragma once
#include<iostream>
#include<list>
#include<string>
#include<fstream>
#include <random>
#include <ctime>
#include <algorithm>
#include"CObiectiv.h"
#include"CRestaurant.h"
#include"CExceptieDeschidereFisierContent.h"
#include"CExceptieSalvareDate.h"
class CPlanificator
{
private:
	std::string plannerMese;
	std::string plannerVizitare;

public:
	CPlanificator() {

	}
	void generatePlannerMese(std::list<CRestaurant*>restauranteAlese,int durata) {
		std::ofstream f(plannerMese);
		if (!f) {
			throw CExceptieSalvareDate("\nNu s - au putut salva datele despre mesele din vacanta.");
		}
		
		f<< "\n\n\t\t\t PLANIFICARE MESE VACANTA:" << durata << "zile";

		
		auto it = restauranteAlese.begin();
		for (int i = 1; i <= durata; i++)
		{
			f << "\n\t\t ZIUA : " << i;
			
			CRestaurant* curr = *it;

			f << "\n\t >MIC-DEJUN: 08:00 - 09:45";
			f << "\n\t" << curr->getNume();
			f<< "\n*Rating:" << curr->getRating();
			f << "\nMeniu" << curr->getMeniu();
			f << "\nPretul mediu/persoana este:" << curr->getPriceMediu();

			
			++it;
			if (it == restauranteAlese.end())
			{
				it = restauranteAlese.begin();
			}
			curr = *it;
			f<< "\n\t >>PRANZ: 13:10 - 15:00";
			f << "\n\t" << curr->getNume();
			f << "\n*Rating:" << curr->getRating();
			f << "\nMeniu" << curr->getMeniu();
			f << "\nPretul mediu/persoana este:" << curr->getPriceMediu();

			++it;
			if (it == restauranteAlese.end())
			{
				it = restauranteAlese.begin();
			}
			curr = *it;
			f<< "\n\t >>>CINA: 19:45 - 20:45";
			f << "\n\t" << curr->getNume();
			f << "\n*Rating:" << curr->getRating();
			f << "\nMeniu" << curr->getMeniu();
			f << "\nPretul mediu/persoana este:" << curr->getPriceMediu();
			f << "\n";
	
			
		}
		f.close();
	}
	void generatePlannerVizitare(std::list<CObiectiv*>obiectiveAlese,int durata) {
		std::ofstream f(plannerVizitare);
		if (!f) {
			throw CExceptieSalvareDate("\nNu s-au putut salva datele despre vizitele din vacanta.");
		}
		
		f << "\n\n\t\t\t PLANIFICARE VIZITE VACANTA:" << durata << "zile";
		auto it = obiectiveAlese.begin();
		for (int i = 1; i <= durata; i++)
		{
			f << "\n\t\t ZIUA : " << i;

			CObiectiv* curr = *it;

			f << "\n\t" << curr->getNume();
			f << "\n\tDescriere: " << curr->getDescriere();
			f << "\n\tRating" << curr->getRating();
			f << "\n\tProgram de vizitare: " << curr->getProgram();
			f << "\n\tDurata de vizitare: " << curr->getDurata();
			f << "\n\tPreturi si Categorii Bilete:";

			for (std::string &j : curr->getCategoriiBilete())
			{
				f << "\n\t" << j;
			}
			f << "\n";

			++it;
			if (it == obiectiveAlese.end())
			{
				it=obiectiveAlese.begin();
			}
		}
		f.close();
	}
	void printPlannerMese()const {
		std::ifstream f(plannerMese);
		if (!f) {
			throw CExceptieDeschidereFisierContent("\nNu s-au putut citi datele despre programul meselor din vacanta");
		}

		std::string line;
		while (std::getline(f, line))
		{
			std::cout << line<<"\n";
		}
		f.close();
	}
	void printPlannerVizitare()const {
		std::ifstream f(plannerVizitare);
		if (!f) {
			throw CExceptieDeschidereFisierContent("\nNu s-au putut citi datele despre programul vizitelor din vacanta");
		}


		std::string line;
		while (std::getline(f, line))
		{
			std::cout << line<<"\n";
		}
		f.close();
	}
	void setPlannerMeseName(const std::string&name) {
		plannerMese = "mese.txt";
	}
	void setPlannerViziteName(const std::string& name) {
		plannerVizitare = name;
	}
	~CPlanificator() {

	}
};