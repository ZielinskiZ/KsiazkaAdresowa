#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;

struct Adresat {
    int id;
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
                kontakt.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                kontakt.imie = pojedynczaDanaAdresata;
                break;
            case 3:
                kontakt.nazwisko = pojedynczaDanaAdresata;
                break;
            case 4:
                kontakt.nrTelefonu = pojedynczaDanaAdresata;
                break;
            case 5:
                kontakt.email = pojedynczaDanaAdresata;
                break;
            case 6:
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
    plik << kontakty[idKontaktu-1].id << '|';
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

            if (idKontaktu != kontakt.id)
                temp << linia << endl;
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

            if (idKontaktu != kontakt.id)
                temp << linia << endl;

            else {
                temp << kontakty[i].id << '|';
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

void dodajOsobeDoListyKontaktow (vector <Adresat> &kontakty) {
    system("cls");
    Adresat kontakt;
    int id;
    string imie, nazwisko, nrTelefonu, email, adres;

    if (kontakty.size() == 0)
        id = 1;
    else
        id = kontakty[kontakty.size() - 1].id + 1;


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

    kontakt.id = id;
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
    cout << "ID: " << kontakty[i].id << endl;
    cout << "Imie i nazwisko:   " << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
    cout << "   Numer telefonu: " << kontakty[i].nrTelefonu << endl;
    cout << "   Email:          " << kontakty[i].email << endl;
    cout << "   Adres:          " << kontakty[i].adres << endl << endl;
}

void szukajKontaktowPoImieniu (vector <Adresat> &kontakty) {
    int iloscOsobODanymImieniu = 0;
    string imie;
    system("cls");
    if (sprawdzCzySaAdresaci (kontakty) == true) {
        cout << "Wpisz imie, ktorego szukasz: ";
        cin >> imie;
        for (int i = 0; i < kontakty.size(); i++) {
            if (imie == kontakty[i].imie) {
                wypiszKontakty(kontakty, i);
                iloscOsobODanymImieniu++;
            }
        }
        if (iloscOsobODanymImieniu == 0)
            cout << "W ksiazce adresowej nie ma osoby o imieniu " << imie << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego.";
        getch();
    }

}

void szukajKontaktowPoNazwisku (vector <Adresat> &kontakty) {
    int iloscOsobODanymNazwisku = 0;
    string nazwisko;
    system("cls");
    if (sprawdzCzySaAdresaci (kontakty) == true) {
        cout << "Wpisz nazwisko, ktorego szukasz: ";
        cin >> nazwisko;
        for (int i = 0; i < kontakty.size(); i++) {
            if (nazwisko == kontakty[i].nazwisko) {
                wypiszKontakty(kontakty, i);
                iloscOsobODanymNazwisku++;
            }
        }
        if (iloscOsobODanymNazwisku == 0)
            cout << "W ksiazce adresowej nie ma osoby o nazwisku " << nazwisko << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego.";
        getch();
    }
}

void pokazWszystkieKontakty (vector <Adresat> &kontakty) {
    system("cls");
    if (sprawdzCzySaAdresaci (kontakty) == true) {
        cout << "Lista kontaktow:" << endl;
        for (int i = 0; i < kontakty.size(); i++) {
            wypiszKontakty(kontakty, i);
        }
        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego.";
        getch();
    }
}

void usunOsobeZListyKontaktow (vector <Adresat> &kontakty) {
    system("cls");
    if (sprawdzCzySaAdresaci (kontakty) == true) {
        int idKontaktu;
        cout << "Usuwanie osoby z listy kontaktow" << endl << endl;
        cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
        cin >> idKontaktu;

        int i = 0;
        for (i; i < kontakty.size(); i++) {
            if (idKontaktu == kontakty[i].id)
                break;
        }
        cout << endl << "Czy na pewno chcesz usunac z listy kontaktow " << kontakty[i].imie << " " << kontakty[i].nazwisko << "?" << endl;
        cout << "Potwierdz naciskajac klawisz 't': ";
        if (getch() == 't') {
            for(auto it = kontakty.begin(); it != kontakty.end(); ++it) {
                if (it->id == idKontaktu) {
                    it = kontakty.erase(it);
                    usunKontaktZPliku(idKontaktu);
                    break;
                }
            }
        }
    }
}

void edytujOsobeZListyKontaktow (vector <Adresat> &kontakty) {
    system("cls");
    if (sprawdzCzySaAdresaci (kontakty) == true) {
        int idKontaktu;
        char wyborUzytkownika;
        cout << "Edycja danych osobowych" << endl << endl;
        cout << "Podaj numer ID adresata, ktorego dane chcesz edytowac: ";
        cin >> idKontaktu;

        int i = 0;
        for (i; i < kontakty.size(); i++) {
            if (idKontaktu == kontakty[i].id) {
                wypiszKontakty(kontakty, i);
                break;
            }
        }

        cout << "Ktore dane chcesz edytowac: " << endl;
        cout << "1. Imie" << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Numer telefonu" << endl;
        cout << "4. Email" << endl;
        cout << "5. Adres" << endl;
        cout << "6. Powrot do menu" << endl;

        cin >> wyborUzytkownika;
        if (wyborUzytkownika == '1') {
            cout << "Wpisz nowe imie: ";
            kontakty[i].imie = wczytajLinie();
            edytujKontaktWPliku(kontakty, idKontaktu, i);
        } else if (wyborUzytkownika == '2') {
            cout << "Wpisz nowe nazwisko: ";
            kontakty[i].nazwisko = wczytajLinie();
            edytujKontaktWPliku(kontakty, idKontaktu, i);
        } else if (wyborUzytkownika == '3') {
            cout << "Wpisz nowy numer telefonu: ";
            kontakty[i].nrTelefonu = wczytajLinie();
            edytujKontaktWPliku(kontakty, idKontaktu, i);
        } else if (wyborUzytkownika == '4') {
            cout << "Wpisz nowy email: ";
            cin >> kontakty[i].email;
            edytujKontaktWPliku(kontakty, idKontaktu, i);
        } else if (wyborUzytkownika == '5') {
            cout << "Wpisz nowy adres: ";
            kontakty[i].adres = wczytajLinie();
            edytujKontaktWPliku(kontakty, idKontaktu, i);
        } else if (wyborUzytkownika == '6') {}
    }
}

int main() {
    vector<Adresat> kontakty;
    wczytajKontaktyZPliku(kontakty);
    char wyborUzytkownika;
    while(true) {
        system("cls");
        cout << "Ksiazka adresowa" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Wyjdz" << endl;

        cin >> wyborUzytkownika;
        if (wyborUzytkownika == '1') {
            dodajOsobeDoListyKontaktow(kontakty);
        } else if (wyborUzytkownika == '2') {
            szukajKontaktowPoImieniu (kontakty);
        } else if (wyborUzytkownika == '3') {
            szukajKontaktowPoNazwisku (kontakty);
        } else if (wyborUzytkownika == '4') {
            pokazWszystkieKontakty (kontakty);
        } else if (wyborUzytkownika == '5') {
            usunOsobeZListyKontaktow (kontakty);
        } else if (wyborUzytkownika == '6') {
            edytujOsobeZListyKontaktow (kontakty);
        } else if (wyborUzytkownika == '9') {
            exit(0);
        }
    }
    return 0;
}
