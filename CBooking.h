#pragma once
#include<string>
#include<list>
#include<iostream>
#include<sstream>
#include"CUtilizator.h"
#include"ALocatie.h"
#include"CRestaurant.h"
#include"CObiectiv.h"
#include"CCazare.h"
#include"CFileManager.h"
#include"placesMaker.h"
#include"AExceptii.h"
#include"CPlanificator.h"
#include<cctype>
#include <conio.h>
class CBooking
{
private:
	static CBooking* instance;
	static CFileManager* CfileInstance;
	static std::list<CUtilizator*> listaClienti;
	static std::list< CRestaurant*> listaRestaurante;
	static std::list< CObiectiv*> listaObiective;
	static std::list< CCazare*> listaCazari;
	static CPlanificator* planner;
public:
	CBooking();
	~CBooking();
	static CBooking* getInstance();
	static void loadUsers(const std::string& filename);
	static void loadPlaces( std::string filename);
	static bool validarePerioada(CCazare* hotel,std::list<std::string>perioadePref);
	static void changePerioada(CUtilizator* user);
	static int compatibilitatePreferinteCulinare(CRestaurant*r,std::list<std::string>&preferinte);
	static bool retryPasswsord(CUtilizator* i);
	static CUtilizator* logIn(const std::string &nume,const std::string&parola);
	static bool validareHotel(CCazare*h, std::list<std::string>tipuriCamere);
	static CCazare* chooseHotel(CUtilizator* user, const std::string&tara);
	static CRestaurant* chooseRestaurant(CUtilizator* user);
	static std::list < CObiectiv*> chooseObiectiveTuristice(CUtilizator* user, const std::string& tara);
	static std::string planificaVacanta(CUtilizator*user);
	static void changeBuget(CUtilizator* user);
	static void changePreferinteCulinare(CUtilizator* user);
	static void changeCategoriiVacante(CUtilizator* user);
	static void changeTipuriCamere(std::list<std::string>&tipuriCamere);
	static void acordaRatingHotel();
	static void acordaRatingRestaurant();
	static void acordaRatingObiectivTuristic();
	static void chooseOptions(CUtilizator*user);
	static void startAPPBooking();
};