#pragma once
#include "AUtilizator.h"
class CUtilizator :public AUtilizator
{
private:
	int varsta;
	std::list<std::string>tipuriCalatorii;
	PortofelElectronic* portofel;
	std::list<std::string>perioadePreferate;
	std::list<std::string>preferinteCulinare;
	int durataVacanta;
	bool vacantaGenerata;

	CPlanificator* plannerCurrent;
public:
	CUtilizator(const std::string& nume,const std::string& parola, int varsta):
		AUtilizator(nume,parola),varsta(varsta){}
	void addType(const std::string& type) {
		tipuriCalatorii.push_back(type);
	}
	void addPerioada(const std::string& perioada) {
		perioadePreferate.push_back(perioada);
	}
	void addPreferinteCulinare(const std::string& preferinta) {
		preferinteCulinare.push_back(preferinta);
	}
	void initiatePlanner() {
		plannerCurrent = new CPlanificator();
	}
	CPlanificator* getPLannerCurrent()
	{
		return plannerCurrent;
	}
	int getVarsta() {
		return varsta;
	}
	void printTipuriCalatorii()const {
		if (tipuriCalatorii.size() == 0)
		{
			std::cout << "\n\tClientul nu a adaugat inca tipurile de calatorii preferate.";
		}
		else {
			std::cout << "\n\t\tTipuri Calatorii:";
			for (auto& i : tipuriCalatorii)
			{
				std::cout << "\n-" << i;
			}
		}
	}
	void printPreferinteCulinare()const {
		if (preferinteCulinare.size() == 0)
		{
			std::cout << "\n\tClientul nu a adaugat inca preferintele culinare.";
		}
		else {
			std::cout << "\n\t\tPreferinte Culinare:";
			for (auto& i : preferinteCulinare)
			{
				std::cout << "\n-" << i;
			}
		}
	}
	void printPerioadePreferate()const {
		if (perioadePreferate.size() == 0)
		{
			std::cout << "\n\tClientul nu a adaugat inca o perioada preferata.";
		}
		else {
			std::cout << "\n\t\tPerioade Preferate:";
			for (auto& i : perioadePreferate)
			{
				std::cout << "\n" << i;
			}
		}
	}
	void printInfoUtilizator()const override {
		std::cout << "\nClientul:" << nume << "\nVarsta:" << varsta ;
		//std::cout <<"\nParola:" <<parola;
		portofel->printBuget();
		printTipuriCalatorii();
		printPerioadePreferate();
		printPreferinteCulinare();
	}
	int getDurataVacanta() {
		return durataVacanta;
	}
	void setDurataVacanta(int nr) {
		durataVacanta = nr;
	}
	void setVacantaGenerataToNotGenerated() {
		vacantaGenerata = false;
	}
	void setVacantaGenerataToGenerated() {
		vacantaGenerata = true;
	}
	bool isGenerated()
	{
		return vacantaGenerata;
	}
	std::list<std::string> getPerioadePref() {
		return perioadePreferate;
	}
	void deleteCurrentPerioade() {
		perioadePreferate.clear();
	}
	void deleteCurrentPreferinteCulinare() {
		preferinteCulinare.clear();
	}
	void deleteCurrentCategoriiVacante() {
		tipuriCalatorii.clear();
	}

	void setPortofel(float buget) {
		portofel = new PortofelElectronic(buget);
	}
	PortofelElectronic* getPortofel() {
		return portofel;
	}

	std::list<std::string>getALLTipuriCalatorii()const {
		return tipuriCalatorii;
	}
	std::list<std::string>getALLPerioadePreferate()const {
		return perioadePreferate;
	}
	std::list<std::string>getALLPreferinteCulinare()const {
		return preferinteCulinare;
	}
	~CUtilizator()override{}
};

