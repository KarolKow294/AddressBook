#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>

using namespace std;

struct Addressee {
    int id;
    string name, surname, phoneNumber, email, address;
};

string readLine() {
    string input = "";
    cin.sync();
    getline(cin, input);
    return input;
}

char readChar() {
    string input = "";
    char character = {0};

    while (true) {
        cin.sync();
        getline(cin, input);

        if (input.length() == 1) {
            character = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return character;
}

int readInt() {
    string input = "";
    int number = 0;

    while (true) {
        cin.sync();
        getline(cin, input);

        stringstream myStream(input);
        if (myStream >> number)
            break;

        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return number;
}

void addAddresseeToFile(vector<Addressee> addressees) {
    fstream file;
    file.open("addressBook.txt", ios::out | ios::app);

    file << addressees[addressees.size() - 1].id << "|"
         << addressees[addressees.size() - 1].name << "|"
         << addressees[addressees.size() - 1].surname << "|"
         << addressees[addressees.size() - 1].phoneNumber << "|"
         << addressees[addressees.size() - 1].email << "|"
         << addressees[addressees.size() - 1].address << "|" << endl;

    file.close();
}

void readAddresseesFromFile(vector<Addressee>& addressees) {
    fstream file;
    string line;
    Addressee person;

    file.open("addressBook.txt", ios::in);

    if (!file.good())
        return;

    while (getline(file, line)) {
        int dataNumber = 1;
            for (int i = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    switch(dataNumber) {
                        case 1: person.id = stoi(line.substr(0, i)); break;
                        case 2: person.name = line.substr(0, i); break;
                        case 3: person.surname = line.substr(0, i); break;
                        case 4: person.phoneNumber = line.substr(0, i); break;
                        case 5: person.email = line.substr(0, i); break;
                        case 6: person.address = line.substr(0, i); break;
                    }
                    line.erase(0, i + 1);
                    i = -1;
                    dataNumber++;
                }
            }
        addressees.push_back(person);
    }
    file.close();
}

int checkTheHighestId(vector<Addressee> addressees) {
    int theHighestId = 0;

    if (!addressees.size())
        return theHighestId;

    theHighestId = addressees[0].id;

    for (int i = 1; i < (int) addressees.size(); i++) {
        if (addressees[i].id > theHighestId)
            theHighestId = addressees[i].id;
    }
    return theHighestId;
}

void addAddressee(vector<Addressee>& addressees) {
    Addressee person;

    cout << "Podaj imie: ";
    person.name = readLine();

    cout << "Podaj nazwisko: ";
    person.surname = readLine();

    cout << "Podaj numer telefonu: ";
    person.phoneNumber = readLine();

    cout << "Podaj email: ";
    person.email = readLine();

    cout << "Podaj adres: ";
    person.address = readLine();

    person.id = checkTheHighestId(addressees) + 1;
    addressees.push_back(person);

    addAddresseeToFile(addressees);
    cout << "\nAdresat zostal dodany" << endl;

    system("pause");
}

void findAddresseesByName(vector<Addressee> addressees) {
    string name;
    bool doesAddresseeExist = false;

    cout << "Podaj imie osoby jaka mamy wyszukac: ";
    name = readLine();

    for (auto& v : addressees) {
        if (v.name == name) {
            doesAddresseeExist = true;
            cout << endl;
            cout << "ID: " << v.id << endl;
            cout << "Imie: " << v.name << endl;
            cout << "Nazwisko: " << v.surname << endl;
            cout << "Telefon: " << v.phoneNumber << endl;
            cout << "Email: " << v.email << endl;
            cout << "Adres: " << v.address << endl;
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie istnieje osoba o takim imieniu";

    cout << endl;
    system("pause");
}

void findAddresseesBySurname(vector<Addressee> addressees) {
    string surname;
    bool doesAddresseeExist = false;

    cout << "Podaj nazwisko osoby jaka mamy wyszukac: ";
    surname = readLine();

    for (auto& v : addressees) {
        if (v.surname == surname) {
            doesAddresseeExist = true;
            cout << endl;
            cout << "ID: " << v.id << endl;
            cout << "Imie: " << v.name << endl;
            cout << "Nazwisko: " << v.surname << endl;
            cout << "Telefon: " << v.phoneNumber << endl;
            cout << "Email: " << v.email << endl;
            cout << "Adres: " << v.address << endl;
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie istnieje osoba o takim nazwisku";

    cout << endl;
    system("pause");
}

void displayListOfAddressees(vector<Addressee> addressees) {
    for (auto& v : addressees) {
        cout << endl;
        cout << "ID: " << v.id << endl;
        cout << "Imie: " << v.name << endl;
        cout << "Nazwisko: " << v.surname << endl;
        cout << "Telefon: " << v.phoneNumber << endl;
        cout << "Email: " << v.email << endl;
        cout << "Adres: " << v.address << endl;
        cout << endl;
    }
    system("pause");
}

void overwritingAddresseesData(vector<Addressee> addressees) {
    fstream file;
    file.open("addressBook.txt", ios::out);

    for (auto& v : addressees) {
        file << v.id << "|"
             << v.name << "|"
             << v.surname << "|"
             << v.phoneNumber << "|"
             << v.email << "|"
             << v.address << "|" << endl;
    }
    file.close();
}

void editingAddresseeData(vector<Addressee>& addressees) {
    char choice;
    int id;
    bool doesAddresseeExist = false;

    system("cls");
    cout << ">>>> EDYCJA ADRESATA <<<<" << endl << endl;
    cout << "Podaj ID adresata ktorego chcesz EDYTOWAC: ";
    id = readInt();

    for (auto& v : addressees) {
        if (v.id == id) {
            doesAddresseeExist = true;
            cout << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;
            cout << "\nWybierz dana do edycji: ";

            choice = readChar();

            switch (choice) {
                case '1':
                    cout << "Nowe imie: ";
                    v.name = readLine();
                break;
                case '2':
                    cout << "Nowe nazwisko: ";
                    v.surname = readLine();
                break;
                case '3':
                    cout << "Nowy numer telefonu: ";
                    v.phoneNumber = readLine();
                break;
                case '4':
                    cout << "Nowy email: ";
                    v.email = readLine();
                break;
                case '5':
                    cout << "Nowy adres: ";
                    v.address = readLine();
                break;
                case '6':
                    return;
                break;
            }
            overwritingAddresseesData(addressees);
            cout << "\nDane adresata zostaly ZMODYFIKOWANE";
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie istnieje adresat o takim ID";

    cout << endl;
    system("pause");
}

void deleteAddressee(vector<Addressee>& addressees) {
    int id;
    bool doesAddresseeExist = false;

    system("cls");
    cout << ">>>> USUWANIE ADRESATA <<<<" << endl << endl;
    cout << "Podaj ID adresata ktorego chcesz USUNAC: ";
    id = readInt();

    vector<Addressee>::iterator position;
    for (position = addressees.begin(); position != addressees.end(); position++) {
        if ((*position).id == id) {
            doesAddresseeExist = true;
            cout << "\nPotwierdz naciskajac klawisz 't': ";

            if(getch() == 't') {
                addressees.erase(position);
                overwritingAddresseesData(addressees);
                cout << "\n\nAdresat zostal USUNIETY";
                break;
            }
            else {
                cout << "\n\nAdresat nie zostal USUNIETY";
                break;
            }
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie istnieje adresat o takim ID";

    cout << endl;
    system("pause");
}

int main()
{
    vector<Addressee> addressees;
    char choice;

    readAddresseesFromFile(addressees);

    while (true) {
        system("cls");
        cout << ">>>> Ksiazka Adresowa <<<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;

        choice = readChar();

        switch (choice) {
            case '1':
                addAddressee(addressees);
            break;
            case '2':
                findAddresseesByName(addressees);
            break;
            case '3':
                findAddresseesBySurname(addressees);
            break;
            case '4':
                displayListOfAddressees(addressees);
            break;
            case '5':
                deleteAddressee(addressees);
            break;
            case '6':
                editingAddresseeData(addressees);
            break;
            case '9':
                exit(0);
            break;
        }
    }
    return 0;
}
