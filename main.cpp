#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;

struct Uzytkownik {
    int idUzytkownika;
    string nazwa;
    string haslo;
};

struct Adresat {
    int idAdresata;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string nrTelefonu;
    string email;
    string adres;
};

string wczytajLinie() {
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;
    cin.sync();
    while (true) {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};
    cin.sync();
    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami) {
    Adresat kontakt;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        } else {
            switch(numerPojedynczejDanejAdresata) {
            case 1:
                kontakt.idAdresata = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                kontakt.idUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                kontakt.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                kontakt.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                kontakt.nrTelefonu = pojedynczaDanaAdresata;
                break;
            case 6:
                kontakt.email = pojedynczaDanaAdresata;
                break;
            case 7:
                kontakt.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return kontakt;
}

void wczytajKontaktyZPliku(vector <Adresat> &kontakty) {
    Adresat kontakt;
    string linia;

    fstream plik;
    plik.open("dane.txt");
    if(plik.good()) {
        while(getline(plik,linia)) {
            kontakt = pobierzDaneAdresata(linia);
            kontakty.push_back(kontakt);
        }
    }
    plik.close();
}

void zapiszKontaktDoPliku(vector <Adresat> &kontakty) {
    int idKontaktu = kontakty.size();
    fstream plik;
    plik.open("dane.txt",ios::out | ios::app);
    plik << kontakty[idKontaktu-1].idAdresata << '|';
    plik << kontakty[idKontaktu-1].idUzytkownika << '|';
    plik << kontakty[idKontaktu-1].imie << '|';
    plik << kontakty[idKontaktu-1].nazwisko << '|';
    plik << kontakty[idKontaktu-1].nrTelefonu << '|';
    plik << kontakty[idKontaktu-1].email << '|';
    plik << kontakty[idKontaktu-1].adres << '|' << endl;
    plik.close();
}

void usunKontaktZPliku(int idKontaktu) {
    Adresat kontakt;
    string linia;
    fstream plik, temp;
    plik.open("dane.txt", ios::in);
    temp.open("temp.txt", ios::out);

    if(plik.good()) {
        while(getline(plik, linia)) {
            kontakt = pobierzDaneAdresata(linia);

            if (idKontaktu != kontakt.idAdresata) {
                temp << linia << endl;
            }
        }
    }

    temp.close();
    plik.close();
    remove("dane.txt");
    rename("temp.txt","dane.txt");
}

void edytujKontaktWPliku(vector <Adresat> &kontakty, int idKontaktu, int i) {
    Adresat kontakt;
    string linia;
    fstream plik, temp;
    plik.open("dane.txt", ios::in);
    temp.open("temp.txt", ios::out);

    if(plik.good()) {
        while(getline(plik, linia)) {
            kontakt = pobierzDaneAdresata(linia);

            if (idKontaktu != kontakt.idAdresata)
                temp << linia << endl;

            else {
                temp << kontakty[i].idAdresata << '|';
                temp << kontakty[i].idUzytkownika << '|';
                temp << kontakty[i].imie << '|';
                temp << kontakty[i].nazwisko << '|';
                temp << kontakty[i].nrTelefonu << '|';
                temp << kontakty[i].email << '|';
                temp << kontakty[i].adres << '|' << endl;
            }
        }
    }

    temp.close();
    plik.close();
    remove("dane.txt");
    rename("temp.txt","dane.txt");
}

bool sprawdzCzySaAdresaci(vector <Adresat> &kontakty) {
    if (kontakty.size() > 0) {
        return true;
    } else {
        cout << "Brak kontaktow w ksiazce adresowej." <<endl;
        Sleep(1500);
        return false;
    }
}

void dodajOsobeDoListyKontaktow (vector <Adresat> &kontakty, int idUzytkownika) {
    system("cls");
    Adresat kontakt;
    int id;
    string imie, nazwisko, nrTelefonu, email, adres;

    if (kontakty.size() == 0) {
        id = 1;
    } else {
        id = kontakty[kontakty.size() - 1].idAdresata + 1;
    }

    cout << "Dodaj nowa osobe do swojej listy kontaktow" << endl;
    cout << "Imie: ";
    imie = wczytajLinie();
    cout << "Nazwisko: ";
    nazwisko = wczytajLinie();
    cout << "Numer telefonu: ";
    nrTelefonu = wczytajLinie();
    cout << "Email: ";
    cin >> email;
    cout << "Adres (miasto, ulica, numer domu/mieszkania): ";
    adres = wczytajLinie();

    kontakt.idAdresata = id;
    kontakt.idUzytkownika = idUzytkownika;
    kontakt.imie = imie;
    kontakt.nazwisko = nazwisko;
    kontakt.nrTelefonu = nrTelefonu;
    kontakt.email = email;
    kontakt.adres = adres;
    kontakty.push_back(kontakt);

    zapiszKontaktDoPliku(kontakty);

    cout << "Kontakt dodany" <<endl;
    Sleep(1000);
}

void wypiszKontakty(vector <Adresat> &kontakty, int i) {
    cout << "ID: " << kontakty[i].idAdresata << endl;
    cout << "Imie i nazwisko:   " << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
    cout << "   Numer telefonu: " << kontakty[i].nrTelefonu << endl;
    cout << "   Email:          " << kontakty[i].email << endl;
    cout << "   Adres:          " << kontakty[i].adres << endl << endl;
}

void szukajKontaktowPoImieniu (vector <Adresat> &kontakty, int idZalogowanegoUzytkownika) {
    int iloscOsobODanymImieniu = 0;
    string imie;
    system("cls");
    if (sprawdzCzySaAdresaci(kontakty)) {
        cout << "Wpisz imie, ktorego szukasz: ";
        cin >> imie;
        for (int i = 0; i < kontakty.size(); i++) {
            if ((imie == kontakty[i].imie) && (idZalogowanegoUzytkownika == kontakty[i].idUzytkownika)) {
                wypiszKontakty(kontakty, i);
                iloscOsobODanymImieniu++;
            }
        }
        if (iloscOsobODanymImieniu == 0) {
            cout << "W ksiazce adresowej nie ma osoby o imieniu " << imie << endl;
        }

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego.";
        getch();
    }
}

void szukajKontaktowPoNazwisku (vector <Adresat> &kontakty, int idZalogowanegoUzytkownika) {
    int iloscOsobODanymNazwisku = 0;
    string nazwisko;
    system("cls");
    if (sprawdzCzySaAdresaci (kontakty) == true) {
        cout << "Wpisz nazwisko, ktorego szukasz: ";
        cin >> nazwisko;
        for (int i = 0; i < kontakty.size(); i++) {
            if ((nazwisko == kontakty[i].nazwisko) && (idZalogowanegoUzytkownika == kontakty[i].idUzytkownika)) {
                wypiszKontakty(kontakty, i);
                iloscOsobODanymNazwisku++;
            }
        }
        if (iloscOsobODanymNazwisku == 0) {
            cout << "W ksiazce adresowej nie ma osoby o nazwisku " << nazwisko << endl;
        }

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego.";
        getch();
    }
}

void pokazWszystkieKontakty (vector <Adresat> &kontakty, int idZalogowanegoUzytkownika) {
    system("cls");
    if (sprawdzCzySaAdresaci (kontakty) == true) {
        cout << "Lista kontaktow:" << endl;
        for (int i = 0; i < kontakty.size(); i++) {
            if (idZalogowanegoUzytkownika == kontakty[i].idUzytkownika) {
                wypiszKontakty(kontakty, i);
            }
        }
        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego.";
        getch();
    }
}

void usunOsobeZListyKontaktow (vector <Adresat> &kontakty, int idZalogowanegoUzytkownika) {
    bool czyUdaloSieUsunacKontakt = false;
    int idKontaktu;

    system("cls");
    if (sprawdzCzySaAdresaci (kontakty)) {
        cout << "Usuwanie osoby z listy kontaktow" << endl << endl;
        cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
        idKontaktu = wczytajLiczbeCalkowita();

        int i = 0;
        for (i; i < kontakty.size(); i++) {
            if ((idKontaktu == kontakty[i].idAdresata) && (idZalogowanegoUzytkownika == kontakty[i].idUzytkownika)) {
                cout << endl << "Czy na pewno chcesz usunac z listy kontaktow " << kontakty[i].imie << " " << kontakty[i].nazwisko << "?" << endl;
                cout << "Potwierdz naciskajac klawisz 't': ";
                if (getch() == 't') {
                    for (int j = 0; j < kontakty.size(); j++) {
                        if (kontakty[j].idAdresata == idKontaktu) {
                            kontakty.erase(kontakty.begin() + j);
                        }
                    }
                    czyUdaloSieUsunacKontakt = true;
                    usunKontaktZPliku(idKontaktu);
                    cout << "Kontakt usuniety." << endl;
                }
            }
        }
    }
    if (czyUdaloSieUsunacKontakt == false) {
        cout << "Nie ma takiego adresata." << endl;
        czyUdaloSieUsunacKontakt = true;
    }
    system("pause");
}

void edytujOsobeZListyKontaktow (vector <Adresat> &kontakty, int idZalogowanegoUzytkownika) {
    bool czyOsobaZostalaEdytowana = false;
    int idKontaktu;
    char wybor;

    system("cls");
    if (sprawdzCzySaAdresaci (kontakty)) {
        cout << "Edycja danych osobowych" << endl << endl;
        cout << "Podaj numer ID adresata, ktorego dane chcesz edytowac: ";
        cin >> idKontaktu;

        int i = 0;
        for (i; i < kontakty.size(); i++) {
            if ((idKontaktu == kontakty[i].idAdresata) && (idZalogowanegoUzytkownika == kontakty[i].idUzytkownika)) {
                wypiszKontakty(kontakty, i);

                cout << "Ktore dane chcesz edytowac: " << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer telefonu" << endl;
                cout << "4. Email" << endl;
                cout << "5. Adres" << endl;
                cout << "6. Powrot do menu" << endl;

                czyOsobaZostalaEdytowana = true;
                wybor = wczytajZnak();
                switch (wybor) {
                case '1':
                    cout << "Wpisz nowe imie: ";
                    kontakty[i].imie = wczytajLinie();
                    edytujKontaktWPliku(kontakty, idKontaktu, i);
                    break;
                case '2':
                    cout << "Wpisz nowe nazwisko: ";
                    kontakty[i].nazwisko = wczytajLinie();
                    edytujKontaktWPliku(kontakty, idKontaktu, i);
                    break;
                case '3':
                    cout << "Wpisz nowy numer telefonu: ";
                    kontakty[i].nrTelefonu = wczytajLinie();
                    edytujKontaktWPliku(kontakty, idKontaktu, i);
                    break;
                case '4':
                    cout << "Wpisz nowy email: ";
                    cin >> kontakty[i].email;
                    edytujKontaktWPliku(kontakty, idKontaktu, i);
                    break;
                case '5':
                    cout << "Wpisz nowy adres: ";
                    kontakty[i].adres = wczytajLinie();
                    edytujKontaktWPliku(kontakty, idKontaktu, i);
                    break;
                case '6':
                    break;
                }
            }
        }
    }
    if (czyOsobaZostalaEdytowana == false) {
        cout << "Nie ma takiego adresata." << endl;
        czyOsobaZostalaEdytowana = true;
    }
    system("pause");
}

Uzytkownik pobierzDaneUzytkownika(string daneUzytkownikaOddzielonePionowymiKreskami) {
    Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneUzytkownikaOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaUzytkownika += daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku];
        } else {
            switch(numerPojedynczejDanejUzytkownika) {
            case 1:
                uzytkownik.idUzytkownika = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.nazwa = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzytkownik;
}

void edytujHasloUzytkownikaWPliku (vector <Uzytkownik> &uzytkownicy,int idZalogowanegoUzytkownika, int i) {
    Uzytkownik uzytkownik;
    string linia;
    fstream plik, temp;
    plik.open("uzytkownicy.txt", ios::in);
    temp.open("uzytkownicy-tymczasowy.txt", ios::out);

    if (plik.good()) {
        while (getline(plik,linia)) {
            uzytkownik = pobierzDaneUzytkownika(linia);

            if (idZalogowanegoUzytkownika != uzytkownik.idUzytkownika)
                temp << linia << endl;
            else {
                temp << uzytkownicy[i].idUzytkownika << '|';
                temp << uzytkownicy[i].nazwa << '|';
                temp << uzytkownicy[i].haslo << '|' << endl;
            }
        }
    }
    temp.close();
    plik.close();
    remove("uzytkownicy.txt");
    rename("uzytkownicy-tymczasowy.txt","uzytkownicy.txt");
}

void zmienHasloUzytkownika (vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    system("cls");
    cout << "Zmiana hasla uzytkownika" << endl;
    cout << "Podaj nowe haslo: ";
    for (int i = 0; i < uzytkownicy.size(); i++) {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = wczytajLinie();
            cout << "Haslo zostalo zmienione." << endl;
            Sleep(1000);
            edytujHasloUzytkownikaWPliku(uzytkownicy, idZalogowanegoUzytkownika, i);
        }
    }
}

void pokazMenuKsiazkiAdresowej () {
    system("cls");
    cout << "Ksiazka adresowa" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "8. Zmien haslo" << endl;
    cout << "9. Wyloguj" << endl;
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik uzytkownik;
    string linia;

    fstream plik;
    plik.open("uzytkownicy.txt");
    if(plik.good()) {
        while(getline(plik,linia)) {
            uzytkownik = pobierzDaneUzytkownika(linia);
            uzytkownicy.push_back(uzytkownik);
        }
    }
    plik.close();
}

void zapiszUzytkownikaDoPliku(vector <Uzytkownik> &uzytkownicy) {
    int idUzytkownika = uzytkownicy.size();
    fstream plik;
    plik.open("uzytkownicy.txt",ios::out | ios::app);
    plik << uzytkownicy[idUzytkownika-1].idUzytkownika << '|';
    plik << uzytkownicy[idUzytkownika-1].nazwa << '|';
    plik << uzytkownicy[idUzytkownika-1].haslo << '|' << endl;
    plik.close();
}

int logowanie(vector <Uzytkownik> &uzytkownicy) {
    system ("cls");
    string nazwa, haslo;
    cout << ">> LOGOWANIE DO PROGRAMU <<" << endl;
    cout << "Podaj nazwe: ";
    nazwa = wczytajLinie();
    int i = 0;
    while (i < uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa == nazwa) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Pozostale proby wpisania hasla: " << 3 - proby << endl << "Wpisz haslo: ";
                haslo = wczytajLinie();
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie jako " << uzytkownicy[i].nazwa << "." << endl;
                    Sleep(1000);
                    return (uzytkownicy[i].idUzytkownika);
                }
            }
            cout << "Wprowadziles 3 razy nieprawidlowe haslo." << endl;
            system ("pause");
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z taka nazwa." << endl;
    Sleep(1000);
    return 0;
}

void rejestracja(vector <Uzytkownik> &uzytkownicy) {
    system ("cls");
    Uzytkownik uzytkownik;
    int id;
    string nazwa, haslo;

    cout << ">> REJESTRACJA NOWEGO UZYTKOWNIKA <<" << endl;
    if (uzytkownicy.size() == 0) {
        id = 1;
    } else {
        id = uzytkownicy[uzytkownicy.size()-1].idUzytkownika + 1;
    }

    cout << "Podaj nazwe uzytkownika: ";
    nazwa = wczytajLinie();
    int i = 0;
    while (i < uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            nazwa = wczytajLinie();
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    haslo = wczytajLinie();

    uzytkownik.idUzytkownika = id;
    uzytkownik.nazwa = nazwa;
    uzytkownik.haslo = haslo;
    uzytkownicy.push_back(uzytkownik);

    zapiszUzytkownikaDoPliku(uzytkownicy);

    cout << "Rejestracja przebiegla pomyslnie." << endl;
    Sleep(1000);
}

void pokazMenuLogowania () {
    system("cls");
    cout << "Logowanie do programu" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "9. Zamknij program" << endl;
}

int main() {
    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> kontakty;
    wczytajUzytkownikowZPliku(uzytkownicy);
    wczytajKontaktyZPliku(kontakty);
    char wybor;
    int idZalogowanegoUzytkownika = 0;

    while(true) {
        if (idZalogowanegoUzytkownika == 0) {
            pokazMenuLogowania();
            wybor = wczytajZnak();
            switch (wybor) {
            case '1':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                break;
            case '2':
                rejestracja(uzytkownicy);
                break;
            case '9':
                exit(0);
                break;
            }
        } else {
            pokazMenuKsiazkiAdresowej();
            wybor = wczytajZnak();
            switch (wybor) {
            case '1':
                dodajOsobeDoListyKontaktow(kontakty, idZalogowanegoUzytkownika);
                break;
            case '2':
                szukajKontaktowPoImieniu(kontakty, idZalogowanegoUzytkownika);
                break;
            case '3':
                szukajKontaktowPoNazwisku(kontakty, idZalogowanegoUzytkownika);
                break;
            case '4':
                pokazWszystkieKontakty(kontakty, idZalogowanegoUzytkownika);
                break;
            case '5':
                usunOsobeZListyKontaktow(kontakty, idZalogowanegoUzytkownika);
                break;
            case '6':
                edytujOsobeZListyKontaktow(kontakty, idZalogowanegoUzytkownika);
                break;
            case '8':
                zmienHasloUzytkownika(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '9':
                idZalogowanegoUzytkownika = 0;
                break;
            }
        }
    }
    return 0;
}
