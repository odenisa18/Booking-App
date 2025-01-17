#pragma once
#include"CCazare.h"
#include"CRestaurant.h"
#include"CObiectiv.h"
#include"ALocatie.h"
#include<list>
#include<string>
#include"CFileManager.h"
#include"CExceptieCreareLocatie.h"
class placesMaker
{
public:
	static ALocatie* createLocation(const std::string& what,const std::string &tara,const std::string& denumire,float rating,const std::string& file)
	{
		//citesc datele din fisier intr o lista de content
		std::list<std::string>content;
		CFileManager::loadContent(file, content);
		std::string redundant;

		if (what == "cazare"){
			CCazare* newCazare_c = nullptr;
			std::string clasificare;
			int nrCamere=0;
			bool admisAnimal=true;
			//parcurg lista si extrag ce ma intereseaza
			for (auto& i : content)
			{
				std::istringstream iss(i);
				std::getline(iss, redundant, ':');
				if (redundant == "Clasificare") {
					std::getline(iss, clasificare, '\n');
				}
				else if (redundant == "Numar de camere") {
					iss >> nrCamere;
				}
				else if (redundant == "Animale de companie") {
					std::string var;
					iss >> var;
					if (var == "Permise")admisAnimal = true;
					else admisAnimal = false;
				}//daca nu am creat inca cazarea,o creez acum
				else if (!newCazare_c) { newCazare_c = new CCazare(tara, denumire, rating,file, clasificare, nrCamere, admisAnimal); }
				
				//continui
				if (redundant == "Tipuri de camere") {
					int nrtypes;
					iss >> nrtypes;
					std::string typeCam;
					float price;
					for (int a = 0; a < nrtypes; a++)
					{
						iss.ignore(1, ',');
						std::getline(iss, typeCam, '-');
						iss >> price;
						newCazare_c->addTipCamera(typeCam, price);
					}
				}
				else if (redundant == "Perioade aglomerate") {
					int nrPer;
					iss >> nrPer;
					std::string Perioada;
					for (int a = 0; a < nrPer; a++)
					{
						iss.ignore(1, ',');
						std::getline(iss, Perioada, ',');
						newCazare_c->addPerioadaAglomerata(Perioada);
					}
				}
				else if (redundant == "Perioade libere") {
					int nrPer;
					iss >> nrPer;
					std::string Perioada;
					for (int a = 0; a < nrPer; a++)
					{
						iss.ignore(1, ',');
						std::getline(iss, Perioada, ',');
						newCazare_c->addPerioadaLibera(Perioada);
					}
				}
			}
			return newCazare_c;
		}
		else if (what == "restaurant"){
			
			CRestaurant* newRestaurant_r = nullptr;
			std::string tipBucatarie, meniu;
			float price=0;
			bool copil=false;
			for (auto i : content)
			{
				std::istringstream iss(i);
				std::getline(iss, redundant, ':');
				
				if (redundant == "Tipuri de bucatarie") {
					std::getline(iss, tipBucatarie, '\n');
				}
				else if (redundant == "Meniu") {
					std::getline(iss, meniu, '>');
				}
				else if (redundant=="Pret mediu meniu persoana") {
					iss >> price;
				}
				else if (redundant=="Meniu pentru copii") {
					std::string var;
					iss >> var;
					if (var == "Disponibil")copil = true;
					else copil = false;
				}
			}
			return newRestaurant_r = new CRestaurant(tara, denumire, rating, file, tipBucatarie, meniu, price, copil);
		}
		else if (what=="obiectiv turistic") {
			
			CObiectiv* newObiectiv_o = nullptr;
			std::string categorie;
			std::string descriere;
			std::string program;
			std::string durata;
			for (auto& i : content)
			{
				std::istringstream iss(i);
				std::getline(iss, redundant, ':');
				if (redundant == "Categorie")
				{
					std::getline(iss, categorie, '\n');
				}
				else if (redundant == "Descriere si informatii cheie") {
					std::getline(iss, descriere, '\n');
				}
				else if (redundant=="Program de vizitare") {
					std::getline(iss, program, '\n');
				}
				else if (redundant == "Durata recomandata pentru vizita completa") {
					std::getline(iss, durata, '\n'); newObiectiv_o = new CObiectiv(tara, denumire, rating,file, categorie, descriere, program, durata);
				}
				else if (redundant == "Pret bilet acces") {
					int nr;
					iss >> nr;
					std::string type;
					for (int a = 0; a < nr;a++) {
						iss.ignore(1, ',');
						std::getline(iss, type, ';');
						newObiectiv_o->addCategorieBiletSiPret(type);
					}
				}
			}
			return newObiectiv_o;
		}
		else {
			throw CExceptieCreareLocatie("\nTipul locatiei nu exista in baza noastra de date.");
		}
	}
};

