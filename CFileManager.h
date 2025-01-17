#pragma once
#include<list>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include"CRestaurant.h"
#include"ALocatie.h"
#include"CCazare.h"
#include"CObiectiv.h"
#include"CRestaurant.h"
#include"CUtilizator.h"
#include"CExceptieDeschidereFisierContent.h"
#include"CExceptieSalvareDate.h"
class CFileManager
{
private:
	static CFileManager* instance;
public:
	CFileManager();
	~CFileManager();
	static CFileManager* getInstance();
	static void loadContent(const std::string filename,std::list<std::string>&content);
	static void saveContentForUser(const std::string& filename,std::list<std::string>tipuriCalatorii,std::list<std::string>perioadePreferate,std::list<std::string>preferinteCulinare);
	static void saveContentForBigFolderLocations(std::list <CCazare*>cazari, std::list < CRestaurant*>restaurante, std::list <CObiectiv* >obiective,const std::string&filename);
	static void saveUsers(const std::string& filename, std::list<CUtilizator*>list, CUtilizator* user);
	static std::string transformFILE(CUtilizator*user);
};

