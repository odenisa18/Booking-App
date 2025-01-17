# MTA TRAVELER: The Trip Assistant You Know You Need

## Descriere

MTA TRAVELER este o aplicație care ajută utilizatorii să își planifice vacanțele, oferind funcționalități pentru alegerea locațiilor de cazare, restaurante pentru mese și atracții turistice, toate într-o interfață simplă și ușor de folosit. Aplicația permite utilizatorilor să își salveze preferințele și să își modifice planurile de călătorie în funcție de nevoi.

## Structura Folderelor

În fereastra **Solution Explorer**, folderele sunt organizate astfel:

### **Singleton**:
- **CFileManager** – Gestionează citirea/scrierea fișierelor text.
- **CBooking** – Gestionează instanțele de clienți și locații (**cazări**, **restaurante**, **obiective turistice**).

### **Utilizatori**:
- **IUtilizator** – Interfață cu metode virtuale.
- **AUtilizator** – Clasă abstractă pentru utilizatori.
- **CUtilizator** – Clasă concretă de tip user.

### **Locații**:
- **ILocatie** – Interfață pentru locații.
- **ALocatie** – Clasă abstractă pentru locațiile concrete.
  - Fiecare clasă concretă are metode și membri comuni, dar și particularități, deoarece reprezintă diverse locații de interes:
    - **CRestaurant**
    - **CCazare**
    - **CObiectivTuristic**

### **Fișiere Program**:
- **locatii.txt** – Fișier ce conține lista locațiilor disponibile.
- **Users.txt** – Fișier ce conține datele utilizatorilor.
- **FISIER_LOCATIE_PARTICULAR** – Fișier specific fiecărui tip de locație.
- **FISIER_USER_PARTICULAR** – Fișier ce păstrează preferințele utilizatorilor.

### **CPlanificator**:
- Clasa care generează programul de vacanță pe baza alegerilor utilizatorului.

### **PortofelElectronic**:
- "Portofelul" virtual al utilizatorului.

## Cum să folosești aplicația

1. **Instalare**:
   - Clonează repository-ul:  
     ```bash
     git clone https://github.com/username/MTA-TRAVELER.git
     ```
   - Deschide proiectul în IDE-ul preferat.

2. **Cum să rulezi aplicația**:
   - Deschide aplicația în terminal sau IDE.
   - La rularea aplicației, vei vedea lista cu clienții înregistrați și locațiile valabile din aplicație.

3. **Logare utilizator**:
   - Dacă ai deja un cont, te poți loga folosind **NUME PRENUME** și parola.
   - Dacă nu ai cont, poți să îți creezi unul și să îți adaugi un fișier cu preferințele.

4. **Meniu principal**:
   - Planifică-ți vacanța alegând **hoteluri**, **restaurante** și **atracții turistice**.
   - Poți să vizualizezi și să modifici programul de vacanță, să îți actualizezi preferințele și să adaugi **ratinguri** pentru locații.

## Contribuții

Dacă vrei să contribui la acest proiect, deschide o problemă sau trimite un pull request cu modificările tale.

## Licență

Distribuit sub licența **MIT**. Vedeți [LICENSE](LICENSE) pentru detalii.

---

**Testare recomandată**: Pentru o testare ușoară, alegeți țara **Franța**. Am adăugat mai multe fișiere cu locații pentru a facilita vizualizarea funcționalităților aplicației.

I hope you like it! :)
