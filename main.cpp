#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>

using namespace std;

struct User {
    int idUser;
    string login, password;
};

struct Addressee {
    int idAddressee;
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

void addUserToFile(vector<User> users) {
    fstream file;
    file.open("Users.txt", ios::out | ios::app);

    file << users[users.size() - 1].idUser << "|"
         << users[users.size() - 1].login << "|"
         << users[users.size() - 1].password << "|" << endl;

    file.close();
}

void readUsersFromFile (vector<User>& users) {
    fstream file;
    string line;
    User person;

    file.open("Users.txt", ios::in);

    if (!file.good())
        return;

    while (getline(file, line)) {
        int dataNumber = 1;
            for (int i = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    switch(dataNumber) {
                        case 1: person.idUser = stoi(line.substr(0, i)); break;
                        case 2: person.login = line.substr(0, i); break;
                        case 3: person.password = line.substr(0, i); break;
                    }
                    line.erase(0, i + 1);
                    i = -1;
                    dataNumber++;
                }
            }
        users.push_back(person);
    }
    file.close();
}

int checkTheHighestId(int theHighestId, int id) {
    if (id > theHighestId)
        theHighestId = id;
    return theHighestId;
}

void addAddresseeToFile(vector<Addressee> addressees, int idOfLoggedInUser) {
    fstream file;
    file.open("Addressees.txt", ios::out | ios::app);

    file << addressees[addressees.size() - 1].idAddressee << "|"
         << idOfLoggedInUser << "|"
         << addressees[addressees.size() - 1].name << "|"
         << addressees[addressees.size() - 1].surname << "|"
         << addressees[addressees.size() - 1].phoneNumber << "|"
         << addressees[addressees.size() - 1].email << "|"
         << addressees[addressees.size() - 1].address << "|" << endl;

    file.close();
}

int readAddresseesFromFile(vector<Addressee>& addressees, int idOfLoggedInUser) {
    fstream file;
    string line;
    Addressee person;
    int theHighestId = 0;

    file.open("Addressees.txt", ios::in);

    if (!file.good())
        return theHighestId;

    while (getline(file, line)) {
        bool doesAddresseeBelongToUser = false;
        int dataNumber = 1;
            for (int i = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    switch(dataNumber) {
                        case 1: person.idAddressee = stoi(line.substr(0, i));
                                theHighestId = checkTheHighestId(theHighestId, stoi(line.substr(0, i)));
                        break;
                        case 2: if (stoi(line.substr(0, i)) == idOfLoggedInUser)
                                    doesAddresseeBelongToUser = true;
                        break;
                        case 3: person.name = line.substr(0, i); break;
                        case 4: person.surname = line.substr(0, i); break;
                        case 5: person.phoneNumber = line.substr(0, i); break;
                        case 6: person.email = line.substr(0, i); break;
                        case 7: person.address = line.substr(0, i); break;
                    }
                    line.erase(0, i + 1);
                    i = -1;
                    dataNumber++;
                }
            }
        if (doesAddresseeBelongToUser)
            addressees.push_back(person);
    }
    file.close();
    return theHighestId;
}

void newUserRegistration(vector<User>& users) {
    User person;

    if (users.empty())
       person.idUser = 1;
    else
       person.idUser = users.back().idUser + 1;

    cout << "Podaj login: ";
    person.login = readLine();

    for (vector<User>::iterator position = users.begin(); position != users.end(); position++) {
        if ((*position).login == person.login) {
            cout << endl;
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            person.login = readLine();
            position = users.begin() - 1;
        }
    }

    cout << "Podaj haslo: ";
    person.password = readLine();

    users.push_back(person);

    addUserToFile(users);
    cout << "\nKonto zalozone pomyslnie." << endl;
    system("pause");
}

int userLogin(vector<User> users) {
    string login, password;
    bool doesUserExist = false;

    cout << "Podaj login: ";
    login = readLine();

    for (auto& v : users) {
        if (v.login == login) {
            doesUserExist = true;
            for (int i = 0; i < 3; i++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - i << ": ";
                password = readLine();

                if (v.password == password) {
                    cout << endl;
                    cout << "Zalogowales sie." << endl;
                    system("pause");
                    return v.idUser;
                }
            }
            cout << "\nPodales 3 razy bledne haslo." << endl;
        }
    }
    if (!doesUserExist)
        cout << "\nNie ma uzytkownika z takim loginem." << endl;

    system("pause");
    return 0;
}

int addAddressee(vector<Addressee>& addressees, int idOfLoggedInUser, int theHighestId) {
    Addressee person;
    int newHighestId = theHighestId + 1;

    person.idAddressee = newHighestId;

    system("cls");
    cout << ">>>> DODAWANIE NOWEGO ADRESATA <<<<" << endl;

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

    addressees.push_back(person);

    addAddresseeToFile(addressees, idOfLoggedInUser);
    cout << "\nAdresat zostal dodany." << endl;
    system("pause");

    return newHighestId;
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
            cout << "ID:             " << v.idAddressee << endl;
            cout << "Imie:           " << v.name << endl;
            cout << "Nazwisko:       " << v.surname << endl;
            cout << "Numer telefonu: " << v.phoneNumber << endl;
            cout << "Email:          " << v.email << endl;
            cout << "Adres:          " << v.address << endl;
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie istnieje osoba o takim imieniu.";

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
            cout << "ID:             " << v.idAddressee << endl;
            cout << "Imie:           " << v.name << endl;
            cout << "Nazwisko:       " << v.surname << endl;
            cout << "Numer telefonu: " << v.phoneNumber << endl;
            cout << "Email:          " << v.email << endl;
            cout << "Adres:          " << v.address << endl;
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie istnieje osoba o takim nazwisku.";

    cout << endl;
    system("pause");
}

void displayListOfAddressees(vector<Addressee> addressees) {
    if (addressees.empty())
        cout << "Lista adresatow jest pusta." << endl;
    else {
        system("cls");
        cout << ">>>> ADRESACI <<<<" << endl;
        cout << "------------------" << endl;

        for (auto& v : addressees) {
            cout << endl;
            cout << "ID:             " << v.idAddressee << endl;
            cout << "Imie:           " << v.name << endl;
            cout << "Nazwisko:       " << v.surname << endl;
            cout << "Numer telefonu: " << v.phoneNumber << endl;
            cout << "Email:          " << v.email << endl;
            cout << "Adres:          " << v.address << endl;
            cout << endl;
        }
    }
    system("pause");
}

void changingDataInFile(vector<Addressee> addressees, int idAddressee, int idOfLoggedInUser) {
    ifstream file;
    ofstream temporaryFile;
    string line;
    file.open("Addressees.txt", ios::in);
    temporaryFile.open("Addressees_temporary.txt", ios::out);

    if (!file.good())
        return;

    while (getline(file, line)) {
        for (int i = 0; i < (int) line.length(); i++) {
            if (line[i] == '|') {
                if (stoi(line.substr(0, i)) == idAddressee) {
                    for (auto& v : addressees) {
                        if (v.idAddressee == idAddressee) {
                            temporaryFile << v.idAddressee << "|"
                                          << idOfLoggedInUser << "|"
                                          << v.name << "|"
                                          << v.surname << "|"
                                          << v.phoneNumber << "|"
                                          << v.email << "|"
                                          << v.address << "|" << endl;
                            break;
                        }
                    }
                }
                else {
                    temporaryFile << line << endl;
                }
                break;
            }
        }
    }
    file.close();
    temporaryFile.close();
    remove ("Addressees.txt");
    rename ("Addressees_temporary.txt", "Addressees.txt");
}

int removingAddresseeFromFile(vector<Addressee> addressees, int idAddressee, int theHighestId) {
    ifstream file;
    ofstream temporaryFile;
    string line;
    int newTheHighestId = 0;
    file.open("Addressees.txt", ios::in);
    temporaryFile.open("Addressees_temporary.txt", ios::out);

    if (!file.good())
        return theHighestId;

    while (getline(file, line)) {
        for (int i = 0; i < (int) line.length(); i++) {
            if (line[i] == '|') {
                if (stoi(line.substr(0, i)) != idAddressee) {
                    newTheHighestId = checkTheHighestId(newTheHighestId, stoi(line.substr(0, i)));
                    temporaryFile << line << endl;
                }
                break;
            }
        }
    }
    file.close();
    temporaryFile.close();
    remove ("Addressees.txt");
    rename ("Addressees_temporary.txt", "Addressees.txt");

    return newTheHighestId;
}

void editingAddresseeData(vector<Addressee>& addressees, int idOfLoggedInUser) {
    char choice;
    int idAddressee;
    bool doesAddresseeExist = false;

    system("cls");
    cout << ">>>> EDYCJA ADRESATA <<<<" << endl << endl;
    cout << "Podaj ID adresata ktorego chcesz EDYTOWAC: ";
    idAddressee = readInt();

    for (auto& v : addressees) {
        if (v.idAddressee == idAddressee) {
            doesAddresseeExist = true;
            cout << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;
            cout << "\nWybierz dane do edycji: ";

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
            changingDataInFile(addressees, idAddressee, idOfLoggedInUser);
            cout << "\nDane adresata zostaly ZMODYFIKOWANE.";
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie ma takiego adresata.";

    cout << endl;
    system("pause");
}

int deleteAddressee(vector<Addressee>& addressees, int theHighestId) {
    int idAddressee;
    bool doesAddresseeExist = false;

    system("cls");
    cout << ">>>> USUWANIE ADRESATA <<<<" << endl << endl;
    cout << "Podaj ID adresata ktorego chcesz USUNAC: ";
    idAddressee = readInt();

    for (vector<Addressee>::iterator position = addressees.begin(); position != addressees.end(); position++) {
        if ((*position).idAddressee == idAddressee) {
            doesAddresseeExist = true;
            cout << "\nPotwierdz naciskajac klawisz 't': ";

            if(getch() == 't') {
                addressees.erase(position);
                theHighestId = removingAddresseeFromFile(addressees, idAddressee, theHighestId);
                cout << "\n\nAdresat zostal USUNIETY.";
                break;
            }
            else {
                cout << "\n\nAdresat nie zostal USUNIETY.";
                break;
            }
        }
    }
    if (!doesAddresseeExist)
        cout << "\nNie ma takiego adresata.";

    cout << endl;
    system("pause");

    return theHighestId;
}

void overwritingUsersData(vector<User> users) {
    fstream file;
    file.open("Users.txt", ios::out);

    for (auto& v : users) {
        file << v.idUser << "|"
             << v.login << "|"
             << v.password << "|" << endl;
    }
    file.close();
}

void userPasswordChange(vector<User>& users, int idOfLoggedInUser) {
    string newPassword = "";

    cout << "Podaj nowe haslo: ";
    newPassword = readLine();

    for (auto& v : users) {
        if (v.idUser == idOfLoggedInUser) {
            v.password = newPassword;
        }
    }

    overwritingUsersData(users);
    cout << "\nHaslo zostalo zmienione." << endl;
    system("pause");
}

int displayMainMenu(vector<User>& users) {
    char choice;
    int idOfLoggedInUser = 0;

    while (true) {
        system("cls");
        cout << ">>>> MENU GLOWNE <<<<" << endl;
        cout << "----------------------" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "9. Koniec programu" << endl;
        cout << "----------------------" << endl;
        cout << "Twoj wybor: ";

        choice = readChar();
        cout << endl;

        switch (choice) {
            case '1':
                newUserRegistration(users);
            break;
            case '2':
                idOfLoggedInUser = userLogin(users);
                    if (idOfLoggedInUser != 0)
                        return idOfLoggedInUser;
            break;
            case '9':
                exit(0);
            break;
        }
    }
}

int displayUserMenu(vector<Addressee>& addressees, vector<User>& users, int idOfLoggedInUser) {
    char choice;
    int theHighestId;

    theHighestId = readAddresseesFromFile(addressees, idOfLoggedInUser);

    while (true) {
        system("cls");
        cout << ">>>> MENU UZYTKOWNIKA <<<<" << endl;
        cout << "--------------------------" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "--------------------------" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "--------------------------" << endl;
        cout << "Twoj wybor: ";

        choice = readChar();
        cout << endl;

        switch (choice) {
            case '1':
                theHighestId = addAddressee(addressees, idOfLoggedInUser, theHighestId);
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
                theHighestId = deleteAddressee(addressees, theHighestId);
            break;
            case '6':
                editingAddresseeData(addressees, idOfLoggedInUser);
            break;
            case '7':
                userPasswordChange(users, idOfLoggedInUser);
            break;
            case '8':
                addressees.clear();
                return 0;
            break;
        }
    }
}

int main()
{
    vector<User> users;
    vector<Addressee> addressees;
    int idOfLoggedInUser = 0;

    readUsersFromFile (users);

    while (true) {
        idOfLoggedInUser = displayMainMenu(users);
        idOfLoggedInUser = displayUserMenu(addressees, users, idOfLoggedInUser);
    }
    return 0;
}
