#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void wczytajOsobyZPliku(vector <Adresat> &adresaci) {
    Adresat adresat;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
    int id = 0;
    fstream plik;
    char znak = '|';
    int pozycjaSeparatora = 0;
    string wycinekLinii = "";
    int iloscZnakow = 0;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good() == false) {
        cout << "Plik nie istnieje" << endl;
    } else if (plik.good() == true) {
        while(getline(plik, wycinekLinii, '|')) {
            switch( iloscZnakow ) {
            case 0:
                adresat.id = atoi( wycinekLinii.c_str() );
                break;
            case 1:
                adresat.imie = wycinekLinii;
                break;
            case 2:
                adresat.nazwisko = wycinekLinii;
                break;
            case 3:
                adresat.numerTelefonu = wycinekLinii;
                break;
            case 4:
                adresat.email = wycinekLinii;
                break;
            case 5:
                adresat.adres = wycinekLinii;
                break;
            }
            if( pozycjaSeparatora == 5 ) {
                adresaci.push_back(adresat);
                iloscZnakow = 0;
                pozycjaSeparatora = 0;
            } else {
                iloscZnakow++;
                pozycjaSeparatora++;
            }
        }
    }
    plik.close();
}

void dodajNowaOsobe(vector <Adresat> &adresaci) {
    Adresat adresat;
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
    fstream plik;
    if (adresaci.size() == 0) {
        id = 1;
    } else {
        id = adresaci[adresaci.size() - 1].id + 1;
    }
    system("cls");
    cout << "Dodawanie nowego adresata" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    adresat.id = id;
    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.email = email;
    adresat.adres = adres;

    adresaci.push_back(adresat);

    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    plik << id << "|";
    plik << imie << "|";
    plik << nazwisko << "|";
    plik << numerTelefonu << "|";
    plik << email << "|";
    plik << adres << "|" << endl;
    plik.close();
    cout << "Nowy adresat zostal dodany do ksiazki adresowej" << endl;

    Sleep(2000);
}

void wyswietlOsobyZPliku(vector <Adresat> &adresaci) {
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
    system("cls");
    cout << "Lista adresatow" << endl;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if(!ifstream("KsiazkaAdresowa.txt", ios::ate).tellg()) {
        cout << "Nie ma jeszcze zadnych zapisanych adresatow" << endl;
    }

    if (plik.good() == false) {
        cout << "Plik nie istnieje!";
        exit(0);
    } else {
        for (int i = 0; i < adresaci.size(); i++) {
            cout << adresaci[i].id << "|" << adresaci[i].imie << "|" <<  adresaci[i].nazwisko << "|" <<  adresaci[i].numerTelefonu << "|" <<  adresaci[i].email << "|" <<  adresaci[i].adres << "|" <<  endl;
        }
    }
    plik.close();
    system("pause");
}

void wyszukiwanieOsobyPoImieniu(vector <Adresat> &adresaci) {
    int licznik = 0;
    string imie, nazwisko, numerTelefonu, email, adres;
    system("cls");
    cout << "Wyszukiwanie adresata" << endl;
    cout << "Podaj imie szukanego adresata: ";
    cin >> imie;
    for (int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].imie == imie) {
            cout << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" <<  endl;
            licznik = 0;
        } else {
            licznik ++;
        }
    }
    if (licznik == adresaci.size()) {
        cout << "Nie ma zapisanego adresata o takim imieniu. Za chwile nastapi przekierowanie do menu glownego" << endl;
    }
    Sleep(2000);
}

void wyszukiwanieOsobyPoNazwisku(vector <Adresat> &adresaci) {
    int id;
    int licznik = 0;
    string imie, nazwisko, numerTelefonu, email, adres;
    system("cls");
    cout << "Wyszukiwanie adresata" << endl;
    cout << "Podaj nazwisko szukanego adresata: ";
    cin >> nazwisko;
    for (int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].nazwisko == nazwisko) {
            cout << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" <<  endl;
            licznik=0;
        } else {
            licznik++;
        }
    }
    if (licznik == adresaci.size()) {
        cout << "Nie ma zapisanego adresata o takim nazwisku. Za chwile nastapi przekierowanie do menu glownego" << endl;
    }
    Sleep(2000);
}

void usuwanieAdresata(vector <Adresat> &adresaci) {
    int id = 0;
    string imie, nazwisko, numerTelefonu, email, adres;
    int licznik = 0;
    char wybor;
    ofstream plik;
    cout << "Podaj id adresata, ktorego chcesz usunac: ";
    cin >> id;
    for (int i = 0; i <= adresaci.size(); ++i) {
        if (adresaci[i].id == id) {
            cout << "Czy na pewno chcesz usunac adresata o id " << id << " ? Jesli tak, wybierz klawisz t. Jesli nie, wybierz klawisz n" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;
            if ((wybor == 't') || (wybor == 'T')) {
                adresaci.erase(adresaci.begin() + i);
                cout << "Adresat zostal usuniety. Za chwile nastapi przekierowanie do menu glownego" << endl;
                licznik = 0;

            } else if ((wybor == 'n') || (wybor == 'N')) {
                cout << "Adresat nie zostal usuniety. Za chwile nastapi przekierowanie do menu glownego" << endl;
                break;
            }
        } else {
            licznik ++;
        }
    }
    if (licznik == adresaci.size() + 1) {
        cout << "Nie ma zapisanego adresata o takim numerze id. Za chwile nastapi przekierowanie do menu glownego" << endl;
    }

    plik.open("KsiazkaAdresowa.txt");
    for (int i = 0; i < adresaci.size(); i++) {
        plik << adresaci[i].id << "|" << adresaci[i].imie << "|" <<  adresaci[i].nazwisko << "|" <<  adresaci[i].numerTelefonu << "|" <<  adresaci[i].email << "|" <<  adresaci[i].adres << "|" <<  endl;
    }

    plik.close();
    Sleep(2000);
}


void edycjaAdresata(vector <Adresat> &adresaci) {
    int id;
    int licznik = 0;
    string imie, nazwisko, numerTelefonu, email, adres;
    char wybor;
    ofstream plik;
    string edytowaneImie, edytowaneNazwisko, edytowanyNumerTelefonu, edytowanyEmail, EdytowanyAdres;
    cout << "Podaj id adresata do edycji: ";
    cin >> id;
    for (int i = 0; i != adresaci.size(); i++) {
        if (adresaci[i].id == id) {
            system("cls");
            cout << "Wybierz kategorie do edycji:" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer Telefonu" << endl;
            cout << "4. Adres email" << endl;
            cout << "5. Adres zamieszkania" << endl;
            cout << "6. Powrot do menu" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;
            if (wybor == '1') {
                cout << "Podaj imie uzytkownika: ";
                cin >> edytowaneImie;
                adresaci[i].imie = edytowaneImie;
                cout << "Dane zostaly zmienione" << endl;
            } else if (wybor == '2') {
                cout << "Podaj nazwisko uzytkownika: ";
                cin >> edytowaneNazwisko;
                adresaci[i].nazwisko = edytowaneNazwisko;
                cout << "Dane zostaly zmienione" << endl;
            } else if (wybor == '3') {
                cout << "Podaj numer telefonu uzytkownika: ";
                cin.sync();
                getline(cin, edytowanyNumerTelefonu);
                adresaci[i].numerTelefonu = edytowanyNumerTelefonu;
                cout << "Dane zostaly zmienione" << endl;
            } else if (wybor == '4') {
                cout << "Podaj email uzytkownika: ";
                cin >> edytowanyEmail;
                adresaci[i].email = edytowanyEmail;
                cout << "Dane zostaly zmienione" << endl;
            } else if (wybor == '5') {
                cout << "Podaj adres uzytkownika: ";
                cin.sync();
                getline(cin, EdytowanyAdres);
                adresaci[i].adres = EdytowanyAdres;
                cout << "Dane zostaly zmienione" << endl;
            } else if (wybor == '6') {
                cout << "Za chwile nastapi przekierowanie do menu glownego";
                break;
            }
        } else {
            licznik ++;
        }
    }
    if (licznik == adresaci.size()) {
        cout << "Nie ma zapisanego adresata o takim numerze id. Za chwile nastapi przekierowanie do menu glownego" << endl;
    }
    plik.open("KsiazkaAdresowa.txt");
    for (int i = 0; i < adresaci.size(); i++) {
        plik << adresaci[i].id << "|" << adresaci[i].imie << "|" <<  adresaci[i].nazwisko << "|" <<  adresaci[i].numerTelefonu << "|" <<  adresaci[i].email << "|" <<  adresaci[i].adres << "|" <<  endl;
    }

    plik.close();
    Sleep(2000);
}

void wyswietlOsobyZPlikuDoEdycjiLubUsuniecia(vector <Adresat> &adresaci) {
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
    system("cls");
    cout << "Lista adresatow" << endl;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if(!ifstream("KsiazkaAdresowa.txt", ios::ate).tellg()) {
        cout << "Nie ma jeszcze zadnych zapisanych adresatow" << endl;
    }

    if (plik.good() == false) {
        cout << "Plik nie istnieje!";
        exit(0);
    } else {
        for (int i = 0; i < adresaci.size(); i++) {
            cout << adresaci[i].id << "|" << adresaci[i].imie << "|" <<  adresaci[i].nazwisko << "|" <<  adresaci[i].numerTelefonu << "|" <<  adresaci[i].email << "|" <<  adresaci[i].adres << "|" <<  endl;
        }
    }
    plik.close();
    cout << endl;
}

int main() {
    vector <Adresat> adresaci;
    char wybor;
    wczytajOsobyZPliku(adresaci);
    while (true) {
        system("cls");
        cout << "1. Dodaj nowego adresata" << endl;
        cout << "2. Wyszukaj adresata po imieniu" << endl;
        cout << "3. Wyszukaj adresata po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;
        if (wybor == '1') {
            dodajNowaOsobe(adresaci);
        } else if (wybor == '2') {
            system("cls");
            cout << "Wyszukiwanie adresata po imieniu" << endl;
            wyszukiwanieOsobyPoImieniu(adresaci);
        } else if(wybor =='3') {
            system("cls");
            cout << "Wyszukiwanie adresata po nazwisku" << endl;
            wyszukiwanieOsobyPoNazwisku(adresaci);
        } else if (wybor == '4') {
            wyswietlOsobyZPliku(adresaci);
        } else if (wybor == '5') {
            system("cls");
            wyswietlOsobyZPlikuDoEdycjiLubUsuniecia(adresaci);
            usuwanieAdresata(adresaci);
        } else if (wybor == '6') {
            system("cls");
            wyswietlOsobyZPlikuDoEdycjiLubUsuniecia(adresaci);
            edycjaAdresata(adresaci);
        } else if (wybor == '9') {
            exit(0);
        }
    }
    return 0;
}
