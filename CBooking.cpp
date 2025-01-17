#include "CBooking.h"
CBooking* CBooking::instance = nullptr;
CFileManager* CBooking::CfileInstance = nullptr;
std::list<CUtilizator*> CBooking::listaClienti = {};
std::list< CRestaurant*>  CBooking::listaRestaurante = {};
std::list< CObiectiv*>  CBooking::listaObiective = {};
std::list< CCazare*>  CBooking::listaCazari = {};
CPlanificator* CBooking::planner = nullptr;
CBooking::CBooking()
{
}

CBooking::~CBooking()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

CBooking* CBooking::getInstance()
{
    if (!instance)
    {
        instance = new CBooking();
    }
    return instance;
}

void CBooking::loadUsers(const std::string&filename)
{
    //salvez datele din fisier intr-o lista continut
    std::list<std::string>content;

    //folosind instanta din CFILEMANAGER
    CfileInstance->loadContent(filename, content);

    std::string nume, parola, file, bani;
    int varsta;
    float bugetDisponibil;
    std::cout << "\nClienti:\n";
    for (auto& u : content)
    {
        std::istringstream iss(u);
        std::getline(iss,nume, ',');
        std::getline(iss, parola, ',');
        iss >> varsta;
        iss.ignore(1, ',');
        iss >>bugetDisponibil;
        iss.ignore(1, ' ');
        std::getline(iss, bani, ',');
        std::getline(iss, file, '\n');

        CUtilizator* newUser_c = new CUtilizator(nume, parola, varsta);

        //fiecare utilizator are asignat un portofel electronic
        newUser_c->setPortofel(bugetDisponibil);
        if (bani == "EURO") {
            newUser_c->getPortofel()->setEuro();
        }
        else if (bani == "RON") {
            newUser_c->getPortofel()->setLei();
        }
        std::list<std::string>contentPref;
        CfileInstance->loadContent(file, contentPref);
        std::string redundant;
        for (auto& a : contentPref)
        {
            std::istringstream iss(a);
            std::getline(iss, redundant, ':');
            int nr;
            std::string temp;
            if (redundant == "Tipuri de calatorii preferate (in ordinea preferintelor)") {
                iss >> nr;
                iss.ignore(1, ',');
                for (int i = 0; i < nr;i++) {
                    std::getline(iss, temp, ';');
                    newUser_c->addType(temp);
                }
            }
            else if (redundant == "Perioade preferate din an pentru vacante") {
                iss >> nr;
                newUser_c->setDurataVacanta(nr);
                iss.ignore(1, ',');
                for (int i = 0; i < nr; i++) {
                    std::getline(iss, temp, ',');
                    newUser_c->addPerioada(temp);
                }
            }
            else if (redundant == "Preferinte culinare") {
                iss >> nr;
                iss.ignore(1, ',');
                for (int i = 0; i < nr; i++) {
                    std::getline(iss, temp, ';');
                    newUser_c->addPreferinteCulinare(temp);
                }
            }
        }
        newUser_c->initiatePlanner();
        newUser_c->setVacantaGenerataToNotGenerated();
        newUser_c->printInfoUtilizator();
        listaClienti.push_back(newUser_c);
        std::cout << "\n\n";
    }
}

void CBooking::loadPlaces( std::string filename)
{
    //salvez datele din fisier intr-o lista continut
    std::list<std::string>content;

    //folosind instanta din CFILEMANAGER
    // decomentare pt testare exceptii::
    //filename = "";
    bool succes = false;
    while (!succes) {
        try {
            CfileInstance->loadContent(filename, content);
            succes = true;
        }
        catch (const AExceptii&e) {
            std::cerr << "\n\nEroare la salvarea datelor despre locatii din fisier:"<<e.what();
            std::cout << "\n\tDoriti sa reincarcati numele fisierului?(DA/NU)";
            std::string q;
            std::cin >> q;
            if (q == "DA")
            {
                std::cout << "\n\tIntroduceti numele fisierului(EXEMPLU.txt):";
                std::cin.ignore();
                std::getline(std::cin, filename);
                //succes = true;
            }
            else exit(-1);
        }
    }

    bool first = true;

    for (auto& p : content)
    {
        //declar variabilele necesare
        std::string what, tara, denumire, file;
        float rating;
        std::istringstream iss(p);
        /*if (first) {
            iss.ignore(3); first = false;
        }*/
        std::getline(iss, what, ',');//what determina ce fel de loc e(restaurant,cazare,obiectiv turistic)
        std::getline(iss, tara, ',');
        std::getline(iss, denumire, ',');
        std::getline(iss, file, ',');
        iss >> rating;

        //creez cu ajutorul unui factory fiecare clasa PLACE necesara aplicatiei 
        try {
            ALocatie* newPlace_p = placesMaker::createLocation(what, tara, denumire, rating, file);
            if (what == "cazare") {
                CCazare* cazare = dynamic_cast<CCazare*>(newPlace_p);
                std::cout << "\n\n\n";
                cazare->printCazare();
                listaCazari.push_back(dynamic_cast<CCazare*>(newPlace_p));
            }
            else if (what == "restaurant") {
                CRestaurant* restaurant = dynamic_cast<CRestaurant*>(newPlace_p);
                std::cout << "\n\n\n";
                restaurant->printRestaurant();
                listaRestaurante.push_back(dynamic_cast<CRestaurant*>(newPlace_p));
            }
            else if (what == "obiectiv turistic") {
                CObiectiv* obiectivTuristic = dynamic_cast<CObiectiv*>(newPlace_p);
                std::cout << "\n\n\n";
                obiectivTuristic->printObiectivTuristic();
                listaObiective.push_back(dynamic_cast<CObiectiv*>(newPlace_p));
            }
        }
        catch (const AExceptii&e) {
            std::cerr << "\nEroare la crearea locatiei in aplicatie:" << e.what();
        }
    }
}

bool CBooking::validarePerioada(CCazare* hotel, std::list<std::string>perioadePref)
{
    if (hotel->searchPerioadaLibera(perioadePref) == "Valid") {
            return true;
    }
    return false;
}

void CBooking::changePerioada(CUtilizator* user)
{
    user->deleteCurrentPerioade();
    std::cout << "\nIntroduceti numarul de zile pentru vacanta(NUMBER):";
    int nr;
    std::cin >> nr;
    user->setDurataVacanta(nr);
    std::cin.ignore();
    std::cout << "\nIntroduceti datele calendaristice(DD.MM.YYYY):";
    std::string data;
    while (nr)
    {
        nr--;
        std::getline(std::cin, data);
        user->addPerioada(data);
    }

    //NECESAR SA ACTUALIZAM SI FISIERUL USERULUI
    std::string filename = user->getNume();
    for (int i = 0; i < filename.size(); i++)
    {
        filename[i] = std::tolower(filename[i]);
    }
    filename.erase(std::remove(filename.begin(), filename.end(), ' '), filename.end());
    filename += ".txt";
    //se actualizeaza si fisierul cu datele despre acest utilizator
    //Pentru Salvarea lor 
   
    try {
        CfileInstance->saveContentForUser(filename, user->getALLTipuriCalatorii(), user->getALLPerioadePreferate(), user->getALLPreferinteCulinare());
    }
    catch (const AExceptii& e) {
        std::cerr << "\nEroare la scrierea in fisier:" << e.what();

    }
    std::cout << "\n\tPerioada a fost schimbata cu succes!";
}

int CBooking::compatibilitatePreferinteCulinare(CRestaurant* r, std::list<std::string>& preferinte)
{
    return 0;
}

bool CBooking::retryPasswsord(CUtilizator* i)
{
    int tryNumber = 3; 
    while (tryNumber > 0) {
            std::cout << "\n\tParola gresita! Mai aveti " << tryNumber<< " incercari.";
            std::cout << "\nIntroduceti parola din nou: ";
            char ch;
            std::string parola;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (!parola.empty()) {
                        parola.pop_back();
                        std::cout << "\b \b";
                    }
                }
                else {
                    parola.push_back(ch);
                    std::cout << "*";
                }
            }
            if (i->getParola() == parola) {
                std::cout << "\nParola corecta!";
                return true; 
            }
            tryNumber--; 
        }
    if (tryNumber == 0) {
        std::cout << "\nAti depasit numarul de incercari permise.";
        return false;
    }
}

CUtilizator* CBooking::logIn(const std::string& nume, const std::string& parola)
{
    //cautam clientul in lista 
    CUtilizator* currentUser = nullptr;
    bool found = false;
    bool parolaInvalida = false;

    for (auto& i : listaClienti){
        //daca gasesc clientul in lista
        if (i->getNume() == nume ) {
            //verific sa aiba parola introdusa la fel cu cea setata
            if (i->getParola() != parola) {
                //daca a gresit parola ii ofer inca 3 sanse de a o introduce
                //daca a reusit sa isi aduca aminte parola corecta se intoarce found=true -ca si cont gasit
                if (retryPasswsord(i) == true) { 
                found = true; 
                parolaInvalida = false;
                currentUser = i;
         
                }
                else {
                    parolaInvalida = true;
                }
            }
            //altfel se intoarce found=true -ca si cont gasit
            else {
                found = true; currentUser = i;
            }
        }
    }
    //daca am gasit clientul il returnez aplicatiei
    if (parolaInvalida)return nullptr;
    if (found) {
        return currentUser;
    }//daca nu l-am gasit il  ajut sa isi faca cont
    else {
        std::string nume;
        std::string parola;
        std::string bani;
        float buget;
        int varsta;
        std::string file;
        std::cout << "\n\t\tHooopa!Se pare ca nu ai cont inca la noi!Hai sa facem unul rapid.";
        std::cout << "\nIntrodu numele complet(FIRSTNAME SECONDNAME):";
        std::getline(std::cin, nume);
        
  
        while (parola.size() < 8) {
            std::cout << "\nAlege o parola de minim 8 caractere:";
            std::getline(std::cin, parola);
        }

        std::cout << "\nIntrodu varsta(Number):";
        std::cin >> varsta;

        std::cout << "\nIntrodu bugetul disponibil(NUMBER EURO/RON):";
        std::cin>> buget;
        std::cin >> bani;
        std::cout << "\nIntrodu numele fisierului cu preferintele tale(EXEMPLU.txt):";
        std::cin >> file;


        CUtilizator* newClient_c = new CUtilizator(nume, parola, varsta);
        newClient_c->setPortofel(buget);
       
        if (bani == "EURO") {
            newClient_c->getPortofel()->setEuro();
        }
        else if (bani == "RON") {
            newClient_c->getPortofel()->setLei();
        }
        std::list<std::string>contentPref;
        CfileInstance->loadContent(file, contentPref);
        std::string redundant;
        for (auto& a : contentPref)
        {
            std::istringstream iss(a);
            std::getline(iss, redundant, ':');
            int nr;
            std::string temp;
            if (redundant == "Tipuri de calatorii preferate (in ordinea preferintelor)") {
                iss >> nr;
                iss.ignore(1, ',');
                for (int i = 0; i < nr; i++) {
                    std::getline(iss, temp, ';');
                    newClient_c->addType(temp);
                }
            }
            else if (redundant == "Perioade preferate din an pentru vacante") {
                iss >> nr;
                newClient_c->setDurataVacanta(nr);
                iss.ignore(1, ',');
                for (int i = 0; i < nr; i++) {
                    std::getline(iss, temp, ';');
                    newClient_c->addPerioada(temp);
                }
            }
            else if (redundant == "Preferinte culinare") {
                iss >> nr;
                iss.ignore(1, ',');
                for (int i = 0; i < nr; i++) {
                    std::getline(iss, temp, ';');
                    newClient_c->addPreferinteCulinare(temp);
                }
            }
        }
        newClient_c->initiatePlanner();
        newClient_c->setVacantaGenerataToNotGenerated();
        newClient_c->printInfoUtilizator();
        CfileInstance->saveUsers("users.txt", listaClienti, newClient_c);
        std::cout << "\nFelicitari!Tocmai ti-ai creat un nou cont!";
        std::cout << "\nCu ce te pot ajuta?";

        listaClienti.push_back(newClient_c);

        return newClient_c;
    }
}
bool CBooking::validareHotel(CCazare* h, std::list<std::string>tipuriCamere)
{
    std::cout << "\nHotel <" << h->getNume() << ">    Gasit la oferta de : ";

    for (auto& i : tipuriCamere) {
        std::cout << "\n\tTip Camera:" << i << "-Pret:" << h->getPretCamera(i);
    }
    std::cout << "\nSunteti de acord cu varianta gasita?(DA/NU)";
    std::string r;
    std::cin >> r;
    if (r == "DA")return true;
    return false;
}

CCazare* CBooking::chooseHotel(CUtilizator* user,const std::string &tara) {
    std::string clasificareHotel, animalCompanie, tipCamera;
    int nrCamere;
    std::cout << "\n\nClasificare hotel (1-5 stele):";
    std::cin.ignore();
    std::getline(std::cin, clasificareHotel);
    std::cout << "\nCu animal de companie?(CU/FARA):";
    std::cin >> animalCompanie;
    std::cout << "\n~Numar de camere(NUMBER):";
    std::cin >> nrCamere;
    std::list<std::string>tipuriCamere;
    for (int i = 0; i < nrCamere; i++) {
        std::cout << "\n~Tipuri de camere(Single/Double/Tryple/Family):";
        std::cin >> tipCamera;
        tipuriCamere.push_back(tipCamera);
    }
    for (auto& h : listaCazari)
    {
        //cautam prima data hotelul in tara ceruta
        if (h->getTara() == tara) {

            //verific daca hotelul are numarul de stele cerut si daca admite animal de companie
            if (h->getClasificare() == clasificareHotel)
            {
                //verific disponibilitatea pentru perioadele preferate 
                // && h->getadmisAnimal() == animalCompanie

                if (validarePerioada(h,user->getPerioadePref()) == true) {
                    //verific daca are tipurile de camere cerute
                    if (h->getTipCamera(tipuriCamere,tipuriCamere.size()) == true) {
  
                        if (validareHotel(h,tipuriCamere) ==true)return h;
                        else continue;
                    }
                    else if(h->getTipCamera(tipuriCamere, tipuriCamere.size()) == false) {
                        std::cout << "\nNu s-au gasit tipurile de camere selectate disponibile.";
                        std::cout << "\nDoresti sa modifici tipurile de camere?(DA/NU)";
                        std::string r;
                        std::cin >> r;
                        if (r == "DA")
                        {
                            h->printTipuriCamere();
                            changeTipuriCamere(tipuriCamere);
                            if (validareHotel(h, tipuriCamere) == true)return h;
                            else continue;
                        }
                        else if(r=="NU"){
                            continue;
                        }
                    }
                }
                else{
                    std::string r;
                    std::cout << "\n\t\tPerioada selectata de tine este ocupata.";
                    std::cout << "\n\tDoriti sa schimbati perioada solicitata pentru vacanta?(DA/NU)";
                    std::cin >> r;
                    if (r == "DA") {
                        h->printPerioadeLibere();
                        changePerioada(user);
                        if (h->getTipCamera(tipuriCamere, tipuriCamere.size()) == true) {

                            if (validareHotel(h, tipuriCamere) == true)return h;
                            else continue;
                        }
                        else if (h->getTipCamera(tipuriCamere, tipuriCamere.size()) == false) {
                            std::cout << "\nNu s-au gasit tipurile de camere selectate disponibile.";
                            std::cout << "\nDoresti sa modifici tipurile de camere?(DA/NU)";
                            std::string r;
                            std::cin >> r;
                            if (r == "DA")
                            {
                                h->printTipuriCamere();
                                changeTipuriCamere(tipuriCamere);
                                if (validareHotel(h, tipuriCamere) == true)return h;
                                else continue;
                            }
                            else if (r == "NU") {
                                continue;
                            }
                        }
                    }
                    else if (r == "NU") {
                        continue;
                    }
                }
            }
        }
    }
    return nullptr;
}
CRestaurant* CBooking::chooseRestaurant(CUtilizator* user)
{
    std::cout << "\n\tDoresti sa actualizezi preferintele culinare?(DA/NU)";
    std::string q;
    std::cin >> q;
    if (q == "DA") {
        changePreferinteCulinare(user);
    }
    std::cout << "\n\tVrei sa bifam si optiunea de meniu pentru copil?(DA/NU)";
    std::cin >> q;
    bool copil;
    if (q == "DA") {
        copil = true;
    }
    else copil = false;
    //caut in lista de restaurante curente unul care sa se potriveasca 
    //cu preferintele culinare actuale
    for (auto& i : listaRestaurante)
    { 
        int compatibil = 0;
        for (auto&r: user->getALLPreferinteCulinare())
        {
            if (i->getTypeKitchen().find(r)!=std::string::npos && copil==i->hasmeniuCopil()&& i->getAles()==false) {
                compatibil++; i->setAles();
            }
        }
        if (compatibil >= 1) {
            return i;
        }
    }
    return nullptr;
}

std::list < CObiectiv*> CBooking::chooseObiectiveTuristice(CUtilizator* user,const std::string& tara)
{
    std::cout << "\n\tDoresti sa actualizezi categoriile de atractii?(DA/NU)";
    std::string q;
    std::cin >> q;
    if (q == "DA") {
        changeCategoriiVacante(user);
    }
    std::list<CObiectiv*>atractii;

    //caut printre atractii 
    for (auto& o : listaObiective)
    {
        //caut sa verific daca tara este compatibila cu cea a obiectivului turistic
        if (o->getTara() == tara)
        {
            //verific ca tipul atractiei sa fie compatibil cu unul din tipurile selectate de utilizator
            for (auto& j : user->getALLTipuriCalatorii())
            {
                if (o->getCategorie().find(j) != std::string::npos)
                {
                    //daca gasesc unul compatibil si vrea sa il viziteze il adaug in lista
                    std::cout << "\n\t\t" << o->getNume();
                    std::cout << "\nAi dori sa vizitezi aceasta locatie?(DA/NU)";
                    std::cin >> q;
                    if (q == "DA") {
                        atractii.push_back(o);
                    }
                    else break;
                }
            }
        }
    }
    return atractii;
}

std::string CBooking::planificaVacanta(CUtilizator* user)
{
    std::cout << "\n\t\tMa bucur ca ai ales aplicatia noastra sa iti planifici vacanta.";
    std::cout << "\n\tOfera-ne mai multe detalii pentru a o face de vis!";
    std::string tara;
    std::cout << "\n\nIn ce tara vrei sa calatoresti?(Contry)";
    std::cin >> tara;

    //cream instanta planner pentru aplicatie
    planner = new CPlanificator();


    //se alege hotelul
    CCazare* currentHotel = chooseHotel(user, tara);

    //daca alegerea este validata
    if (currentHotel) {
        //se aleg restaurantele pentru servirea mesei(MIC-DEJUN/PRANZ/CINA)
        std::cout << "\n\tSa incepem alegerea restaurantelor pentru servirea meselor.";
        std::list<CRestaurant*>restauranteAlese;

        std::cout << "\nAlegeti restaurantul pentru micul-dejun:";
        restauranteAlese.push_back(chooseRestaurant(user));

        std::cout << "\nAlegeti restaurantul pentru pranz:";
        restauranteAlese.push_back(chooseRestaurant(user));

        std::cout << "\nAlegeti restaurantul pentru cina:";
        restauranteAlese.push_back(chooseRestaurant(user));

        //se aleg obiectivele turistice
        std::list<CObiectiv*>obiectiveAlese;
        std::cout << "\nAlegeti obiectivele care va reprezinta cel mai bine dorintele.";
        obiectiveAlese=chooseObiectiveTuristice(user,tara);


        //generam cele doua programe de MASA,respectiv VIZITARE

        user->getPLannerCurrent()->setPlannerMeseName("mese.txt");

        try {
            user->getPLannerCurrent()->generatePlannerMese(restauranteAlese, user->getDurataVacanta());
        }
        catch (const AExceptii& e) {
            std::cerr << "\nEroare la scrierea in fisier:" << e.what();
        }

        user->getPLannerCurrent()->setPlannerViziteName("vizite.txt");
       
        try {
            user->getPLannerCurrent()->generatePlannerVizitare(obiectiveAlese, user->getDurataVacanta());
        }
        catch (const AExceptii& e) {
            std::cerr << "\nEroare la scrierea in fisier:" << e.what();
        }

        //marcam pentru acest user ca avand vacanta deja generata
        user->setVacantaGenerataToGenerated();

        std::cout << "\n\tVacanta ta a fost planificata cu succes!\n";
        return "Finalizat.";
    }
    else {
        std::cout << "\nNu au fost gasite variante de cazare pentru perioada selectata!";
        return "Nefinalizat.";
    }
}

void CBooking::changeBuget(CUtilizator* user)
{
    float bugetModificat=9;
    std::string answer;
    std::cout << "\nDoriti sa retrageti banii sau sa adaugati altii la contul curent?(ADAUG/RETRAG)";
    std::cin >> answer;
    if (answer == "ADAUG") {
        user->getPortofel()->actualizeazaBuget(bugetModificat);
    }
    else {
        user->getPortofel()->setTozero();
    }
}

void CBooking::changePreferinteCulinare(CUtilizator* user)
{
    user->deleteCurrentPreferinteCulinare();
    std::cout << "\nIntroduceti numarul de preferinte culinare pentru vacanta(NUMBER):";
    int nr;
    std::cin >> nr;
    std::cin.ignore();
    std::cout << "\nIntroduceti abordarile culinare in ordinea preferintelor:";
    std::string preferinta;
    while (nr)
    {
        nr--;
        std::getline(std::cin, preferinta);
        user->addPreferinteCulinare(preferinta);
    }
    //NECESAR SA ACTUALIZAM SI FISIERUL USERULUI
    std::string filename=user->getNume();
    for (int i = 0; i < filename.size(); i++)
    {
        filename[i]=std::tolower(filename[i]);
    }
    filename.erase(std::remove(filename.begin(), filename.end(), ' '), filename.end());
    filename += ".txt";
    //se actualizeaza si fisierul cu datele despre acest utilizator
    //Pentru Salvarea lor 
    try {
        CfileInstance->saveContentForUser(filename, user->getALLTipuriCalatorii(), user->getALLPerioadePreferate(), user->getALLPreferinteCulinare());
    }
    catch (const AExceptii& e) {
        std::cerr << "\nEroare la scrierea in fisier:" << e.what();

    }
    std::cout << "\n\tPreferintele culinare au fost modificate cu succes!";
}

void CBooking::changeCategoriiVacante(CUtilizator* user)
{
    user->deleteCurrentCategoriiVacante();
    std::cout << "\nIntroduceti numarul de categorii de vacanta(NUMBER):";
    int nr;
    std::cin >> nr;
    std::cin.ignore();
    std::cout << "\nIntroduceti categoriile in ordinea preferintelor:";
    std::string category;
    while (nr)
    {
        nr--;
        std::getline(std::cin, category);
        user->addType(category);
    }

    //NECESAR SA ACTUALIZAM SI FISIERUL USERULUI
    std::string filename = user->getNume();
    for (int i = 0; i < filename.size(); i++)
    {
        filename[i] = std::tolower(filename[i]);
    }
    filename.erase(std::remove(filename.begin(), filename.end(), ' '), filename.end());
    filename += ".txt";
    //se actualizeaza si fisierul cu datele despre acest utilizator
    //Pentru Salvarea lor 
    try {
        CfileInstance->saveContentForUser(filename, user->getALLTipuriCalatorii(), user->getALLPerioadePreferate(), user->getALLPreferinteCulinare());
    }
    catch (const AExceptii& e) {
        std::cerr << "\nEroare la scrierea in fisier:" << e.what();

    }

    std::cout << "\n\tCategoriile de vacanta au fost modificate cu succes!";
}

void CBooking::changeTipuriCamere(std::list<std::string>&tipuriCamere)
{
    tipuriCamere.clear();
    std::cout << "\nIntroduceti numarul de camere de vacanta(NUMBER):";
    int nr;
    std::cin >> nr;
    std::cin.ignore();
    std::cout << "\nIntroduceti tipurile de camere in ordinea preferintelor:";
    std::string type;
    while (nr)
    {
        nr--;
        std::getline(std::cin, type);
        tipuriCamere.push_back(type);
    }
}

void CBooking::acordaRatingHotel()
{
    std::cout << "\nCarui hotel doresti sa ii acorzi o nota?";
    std::cin.ignore();
    std::string tempName;
    std::getline(std::cin, tempName);
    bool found =false;
    for (auto& h : listaCazari)
    {
        if (h->getNume() == tempName)
        {
            h->changeRating();
            std::cout << "\n\tRating adaugat cu succes!";
            found = true;
            std::string filenameHotel = h->getFilename();
           
            try {
                CfileInstance->saveContentForBigFolderLocations(listaCazari, listaRestaurante, listaObiective, "locatii.txt");
            }
            catch (const AExceptii& e) {
                std::cerr << "\nEroare la scrierea in fisier:" << e.what();

            }
        }
    }
    if (!found) std::cout << "\n\tNu a fost gasit acest hotel!";
}

void CBooking::acordaRatingRestaurant()
{
    std::cout << "\nCarui restaurant doresti sa ii acorzi o nota?";
    std::cin.ignore();
    std::string tempName;
    std::getline(std::cin, tempName);
    bool found = false;
    for (auto& r : listaRestaurante)
    {
        if (r->getNume() == tempName)
        {
            r->changeRating();
            std::cout << "\n\tRating adaugat cu succes!";
            found = true;
            std::string filenameRestaurant = r->getFilename();
            try {
                CfileInstance->saveContentForBigFolderLocations(listaCazari, listaRestaurante, listaObiective, "locatii.txt");
            }
            catch (const AExceptii& e) {
                std::cerr << "\nEroare la scrierea in fisier:" << e.what();

            }
        }
    }
    if(!found)std::cout << "\n\tNu a fost gasit acest restaurant!";
}

void CBooking::acordaRatingObiectivTuristic()
{
    std::cout << "\nCarui obiectiv turistic doresti sa ii acorzi o nota?";
    std::cin.ignore();
    std::string tempName;
    std::getline(std::cin, tempName);
    bool found = false;
    for (auto& o : listaObiective)
    {
        if (o->getNume() == tempName)
        {
            o->changeRating();
            std::cout << "\n\tRating adaugat cu succes!";
            found = true;
            std::string filenameObiectiv = o->getFilename();
            try {
                CfileInstance->saveContentForBigFolderLocations(listaCazari, listaRestaurante, listaObiective, "locatii.txt");
            }
            catch (const AExceptii& e) {
                std::cerr << "\nEroare la scrierea in fisier:" << e.what();

            }
        }
    }
    if (!found) std::cout << "\n\tNu a fost gasit acest obiectiv turistic!";
}

void CBooking::chooseOptions(CUtilizator* user)
{
    //incepe meniul propriu-zis
    bool go = true;
    while (go) {
        std::cout << "\n\n\t#1. Planifica o calatorie";
        std::cout << "\n\n\t#2. Afiseaza program pentru mese";
        std::cout << "\n\n\t#3. Afiseaza program pentru vizite";
        std::cout << "\n\n\t#4. Modifica perioadele preferate";
        std::cout << "\n\n\t#5. Modifica bugetul de calatorie";
        std::cout << "\n\n\t#6. Modifica preferintele culinare";
        std::cout << "\n\n\t#7. Modifica categoriile de vacante";
        std::cout << "\n\n\t#8. Adauga Rating Hotel";
        std::cout << "\n\n\t#9. Adauga Rating Restaurant";
        std::cout << "\n\n\t#10. Adauga Rating Obiectiv Turistic";
        std::cout << "\n\n\t#11. Iesire din Aplicatie";
        std::cout << "\n\n\tAlege o optiune:";
        int alegere;
        std::cin >> alegere;
        switch (alegere) {
        case 1: {
            if (planificaVacanta(user) == "Finalizat.")break;
            break;
        }
        case 2: {
            if (user->isGenerated() == true) {
                try {
                    user->getPLannerCurrent()->printPlannerMese();
                    }
                catch (const AExceptii&e) {
                    std::cerr << "\nEroare la citirea datelor din fisier:" << e.what();
                }
            }
            else {
                std::cout << "\nNu ai inca o vacanta planificata!Planifica una acum.";
            }
            break;
        }
        case 3: {
            if (user->isGenerated() == true){
                try {
                    user->getPLannerCurrent()->printPlannerVizitare();
                }
                catch (const AExceptii& e) {
                    std::cerr << "\nEroare la citirea datelor din fisier:" << e.what();
                }
            }
            else {
                std::cout << "\nNu ai inca o vacanta planificata!Planifica una acum.";
            }
            break;
        }
        case 4: {
            changePerioada(user);
            break;
        }
        case 5: {
            changeBuget(user);
            break;
        }
        case 6: {
            changePreferinteCulinare(user);
            break;
        }
        case 7: {
            changeCategoriiVacante(user);
            break;
        }
        case 8: {
            acordaRatingHotel();
            break;
        }
        case 9: {
            acordaRatingRestaurant();
            break;
        }
        case 10: {
            acordaRatingObiectivTuristic();
            break;
        }
        case 11: {
            std::cout << "\nPress Enter to close the window...";
            std::cin.ignore();
            std::cin.get();
            go = false;
        }
        default: break;
        }
        if (go)
        {
            std::cout << "\n\n\tDoresti sa continui?(DA/NU):";
            std::string q;
            std::cin >> q;
            if (q == "NU") {
                std::cout << "\nPress Enter to close the window...";
                std::cin.ignore();
                std::cin.get();
                go = false;
            }
        }
    }
}

void CBooking::startAPPBooking()
{
    //instantiez CFileManager
    CfileInstance = CFileManager::getInstance();

    //incarc toate datele utile aplicatiei:
    ///users,cazari,restaurante,obiective turistice.
    loadUsers("Users.txt");
    loadPlaces("locatii.txt");

    //se deschide aplicatia
    std::cout << "\n\n\t\t\tBOOKING by Denisa.com";
    std::cout << "\n\t\tMeniu principal:";
    std::cout << "\nIntra in cont";
    std::cout << "\n\tNume:";
    std::string nume;
    std::getline(std::cin,nume);
    std::cout << "\n\tParola:";
    char ch;
    std::string parola;
    while ((ch = _getch()) != '\r') {  
        if (ch == '\b') {  
            if (!parola.empty()) {
                parola.pop_back();
                std::cout << "\b \b";  
            }
        }
        else {
            parola.push_back(ch);
            std::cout << "*";  
        }
    }
    //std::getline(std::cin, parola);

    //se logheaza user-ul fie daca are deja cont,fie daca nu (are isi creaza)
    CUtilizator*currentUser=logIn(nume,parola);

    //alege optiunile din meniu
    if (currentUser) {
        chooseOptions(currentUser);
    }
}
