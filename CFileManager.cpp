#include "CFileManager.h"
CFileManager* CFileManager::instance = nullptr;

CFileManager::CFileManager()
{
}

CFileManager::~CFileManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

CFileManager* CFileManager::getInstance()
{
	if (!instance)
	{
		instance = new CFileManager();
	}
	return instance;
}

void CFileManager::loadContent(const std::string filename, std::list<std::string>& content)
{
	std::ifstream f(filename);
	if (!f) {
		throw CExceptieDeschidereFisierContent("\nFisierul nu a putut fi deschis sau este invalid!");
	}
	std::string linie;
	while (std::getline(f, linie)) {
		content.push_back(linie);
	}
	f.close();
}

void CFileManager::saveContentForUser(const std::string& filename, std::list<std::string>tipuriCalatorii, std::list<std::string>perioadePreferate, std::list<std::string>preferinteCulinare)
{
	std::ofstream f(filename);
	if (!f)
	{
		throw CExceptieSalvareDate("\nDatele nu au putut fi salvate in fisier.");
	}
	f << "Tipuri de calatorii preferate (in ordinea preferintelor):";
	f << tipuriCalatorii.size() << ",";
	for (auto& i : tipuriCalatorii) {
		f << i << ";";
	}
	f << "\nPerioade preferate din an pentru vacante:";
	f << perioadePreferate.size() << ",";
	for (auto& i : perioadePreferate) {
		f << i << ",";
	}
	f << "\nPreferinte culinare:";
	f << preferinteCulinare.size() << ",";
	for (auto& i : preferinteCulinare) {
		f << i << ";";
	}

	f.close();
}

void CFileManager::saveContentForBigFolderLocations(std::list <CCazare*>cazari, std::list < CRestaurant*>restaurante, std::list <CObiectiv* >obiective, const std::string& filename)
{
	std::ofstream f(filename);
	if (!f)
	{
		throw CExceptieSalvareDate("\nDatele nu au putut fi salvate in fisier.");
	}
	//f << "redundant\n";
	for (auto& i : cazari)
	{
		f << "cazare," << i->getTara() << "," << i->getNume() << "," << i->getFilename() << "," << i->getRating() << " / 5\n";
	}
	for (auto& i : restaurante) {
		f << "restaurant," << i->getTara() << "," << i->getNume() << "," << i->getFilename() << "," << i->getRating() << " / 5\n";
	}
	for (auto& i : obiective) {
		f << "obiectiv turistic," << i->getTara() << "," << i->getNume() << "," << i->getFilename() << "," << i->getRating() << " / 5\n";
	}
	f.close();
}
std::string CFileManager::transformFILE(CUtilizator* user)
{
	std::string filename = user->getNume();
	for (int i = 0; i < filename.size(); i++)
	{
		filename[i] = std::tolower(filename[i]);
	}
	filename.erase(std::remove(filename.begin(), filename.end(), ' '), filename.end());
	filename += ".txt";
	return filename;
}

void CFileManager::saveUsers(const std::string& filename, std::list<CUtilizator*> list, CUtilizator* user)
{
	std::ofstream f(filename);
	if (!f)
	{
		throw CExceptieSalvareDate("\nDatele nu au putut fi salvate in fisier.");
	}
	for (auto& i : list)
	{
		std::string filen = transformFILE(i);
		
		f << i->getNume() << "," << i->getParola() << "," << i->getVarsta() << "," <<i->getPortofel()->getBuget()<<" "<<i->getPortofel()->typeBancnota()<<","<<filen<<"\n";
	}
	std::string filen = transformFILE(user);
	f << user->getNume() << "," << user->getParola() << "," << user->getVarsta() << "," << user->getPortofel()->getBuget() << " " << user->getPortofel()->typeBancnota() << "," << filen<<"\n";
	f.close();
}