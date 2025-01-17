#pragma once
#include<iostream>
class PortofelElectronic
{
private:
	float bugetCurent;
	float taxePlatite;
	bool euro;
	bool lei;
public:
	PortofelElectronic(float bugetCurent):
		bugetCurent(bugetCurent){}

	void actualizeazaBuget(float newBuget_b) {
		bugetCurent = newBuget_b;
	}

	void platesteTaxa(float taxa) {
		bugetCurent -= taxa;
		taxePlatite += taxa;
	}

	void printBuget()const {
		std::cout <<"\nBuget disponibil:" << bugetCurent;
		if (euro==true) { std::cout << " Euro."; }
		else if (lei==true) { std::cout << " RON."; }
	}
	void setTozero()
	{
		bugetCurent = 0;
	}
	void setEuro() {
		euro = true;
		lei = false;
	}
	void setLei() {
		lei = true;
		euro = false;
	}
	float getBuget() {
		return bugetCurent;
	}
	std::string typeBancnota() {
		if (euro == true) {
			return "EURO";
		}
		else return "RON";
	}
	~PortofelElectronic() {

	}
};

