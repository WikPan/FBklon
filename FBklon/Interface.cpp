#include "Interface.h"

Interface::Interface() {
	database.loadDatabase();
}
int Interface::choice(int maxChoice) {
	bool correct = true;
	int input;
	while (correct) {
		cout << "Please enter your choice:\n";
		cin >> input;
		if (input < 1 || input > maxChoice) {
			correct = false;
			cout << "Entered choice is wrong! Please enter number from range (1->" << maxChoice << ")" << endl;
			system("PAUSE");
			system("CLS");
		}
	}
	return input;
}
bool Interface::startupScreen() {
	cout << "Hi what do you want to do?\n";
	cout << "pres 1. to Login\n";
	cout << "pres 2. to Register\n";
	//Przywitac uzytkownika i ma podac dwa stringi - login i password
	//1. login 2. register
	//1. login 
	string login, password;



	int input = choice(3); //Tutaj zamiast 3 max liczba opcji

	if (input == 1) {
		cout << "You chose to Login\n";
		cout << "Login: ";
		cin >> login;
		cout << "\n Password: ";
		cin >> password;
		//login = "admin";
		//password = "admin1";
		currentUser = make_shared<User>(databaseInterface.logIn(database, login, password));
		if (currentUser == nullptr) {
			//Nie udalo sie
			cout << "Wrong password or login";
			return false;
		}
		//zalogowano
		cout << "You have succesfull login\n";
	}
	else if (input == 2) {
		cout << "You chose to Register\n";
		cout << "Your login: ";
		cin >> login;
		cout << "\nYour password: ";
		cin >> password;
	}
	else {
		cout << "THIS OPTIONS IS FORBBIDEN";
	}
}
bool Interface::options() {



	int input = choice(3); //Tutaj zamiast 3 max liczba opcji
}