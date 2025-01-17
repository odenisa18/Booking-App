# Booking-App

#MTA TRAVELER the trip assistant that you know you need

##Structura folderelor
In fereastra Solution Explorer,folderele sunt organizate dupa cum urmeaza:
--Singleton:
       *CFileManager se ocupa cu gestionarea(citirea/scrierea)
           tuturor fisierelor text ce vor fi utilizate in cadrul programului.
       *CBooking gestioneaza instantele de clienti si locatii(cazari/obiective turistice/restaurante) este responsabila pentru initializarea si 
         legatura dintre acestea.
--Utilizatori:
       *IUtilizator este o clasa de tip interface cu metode comune virtuale.(concept folosit:polimorfism).
        **AUtilizator este o clasa abstracta din care derivez utilizatorii acestei aplicatii.(concept folosit:mostenire).
         ***CUtilizator este clasa concreta de tip user.
--Locatii:
       *ILocatie este o clasa de tip interfata cu metode pure virtuale din care derivez locatiile aplicatiei.
        **ALocatie este o clasa abstracta cu membri comuni pentru clasele concrete:
         +fiecare clasa concreta are metode+membri comuni,dar si particulari deoarece acestea reprezinta diverse locatii de interes.
          ***CRestaurant
          ***CCazare
          ***CObiectivTuristic
--Fisiere Program:
       *locatii.txt fisier text cu liste ce cuprind:
         TIP_LOCATIE,TARA,DENUMIRE,FISIER_LOCATIE_PARTICULAR,RATING
       *Users.txt fisier text cu liste ce cuprind:
         NUME PRENUME UTILIZATOR,PAROLA,VARSTA,BUGET BANCNOTA,FISIER_USER_PARTICULAR
       *FISIER_LOCATIE_PARTICULAR : este specific pentru fiecare tip de cazare si contine detalii specifice despre acestea
       *FISIER_USER_PARTICULAR : retine pentru fiecare utilizator preferintele sale sub forma unui fisier text
--CPlanificator:
       *este clasa de baza a aplicatiei care se bazeaza pe generarea programului de mese si vizitare din vacanta
--PortofelElectronic:
       *este "portofelul" virtual al userului

###Utilizare
La rularea aplicatiei, in consola se afiseaza lista cu clientii inregistrati si toate locatiile valabile din aplicatie.
Logarea in aplicatie:
     -Daca persoana are deja cont se poate loga direct prin (NUME PRENUME) si parola
        -avand 3 incercari de a introduce parola corecta
           -- altfel apare un mesaj de eroare si il ajuta sa isi creeze un cont prin introducerea datelor aferente si a unui fisier de preferinte

           **Toate modificarile sunt actualizate si salvate si vor fi regasite chiar si dupa inchiderea si redeschiderea aplicatiei.

           MENIUL PRINCIPAL permite:
           1. PLanificarea unei calatorii
           1.1. Prin posibilitatea alegerii hotelului pe baza unor recomandari
           1.2. Selectarea restaurantelor pentru cele 3 mese din zi (MIC-DEJUN/PRANZ/CINA)
           1.3. Selectarea atractiilor pe care doreste sa le viziteze in zilele de vacanta

           2. Afisarea programului cu mesele de vacanta daca acesta exista

           3. Afisarea programului cu mesele de vacanta daca acesta exista

           4. Modifica perioadele preferate

           5. Modifica bugetul de calatorie

           6. Modifica preferintele culinare

           7. Modifica categoriile de vacante

           8. Adaugare Rating Hotel

           9. Adauga Rating Restaurant

           10. Adauga Rating Obiectiv Turistic

           11. Iesire din Aplicatie

PENTRU TESTARE RECOMAND ALEGEREA TARII FRANTA,am adaugat mai multe fisiere cu locatii pentru a avea o usoara vizualizare a functionalitatilor.

I hope you like it.
:)
