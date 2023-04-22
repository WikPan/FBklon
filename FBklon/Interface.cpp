#include "Interface.h"

Interface::Interface() {
	database.loadDatabase();
}
int Interface::choice(int maxChoice) {
	bool correct = false;
	int input;
	while (!correct) {
		cout << "Please enter your choice:\n";
		cin >> input;
		if (input < 1 || input > maxChoice) {
			correct = false;
			cout << "Entered choice is wrong! Please enter number from range (1->" << maxChoice << ")" << endl;
			system("PAUSE");
			system("CLS");
		}
        correct = true;
	}
	return input;
}

void Interface::startupScreen() {
    cout << "Welcome to BookFace?\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
    string login, password;

    int input = choice(3); //Tutaj zamiast 3 max liczba opcji

    if (input == 1) {
        bool logowaniePoprawne = false;
        while (!logowaniePoprawne) {
            cout << "*****LOGIN PAGE*****\n";
            cout << "Login: ";
            cin >> login;
            cout << "\nPassword: ";
            cin >> password;
            currentUser = databaseInterface.logIn(database, login, password);
            if (currentUser == nullptr) {
                cout << "Wrong login or password\n";
                system("pause");
                system("cls");
               
            }
            
        }
        cout << "You have succesfully logged in!\n";
        system("pause");
        system("cls");
    }
    else if (input == 2) {
        cout << "******REGISTER PAGE*******\n";
        cout << "login: ";
        cin >> login;
        cout << "\npassword: ";
        cin >> password;
    }
    else {
        cout << "Goodbye!";
    }
}
bool Interface::options() {


	int input = choice(3); //Tutaj zamiast 3 max liczba opcji
    return true;
}