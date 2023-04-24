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
        bool logowaniePoprawne = true;
        do {
            logowaniePoprawne = true;
            cout << "*****LOGIN PAGE*****\n";
            cout << "Login: ";
            cin >> login;
            cout << "\nPassword: ";
            cin >> password;
            currentUser = databaseInterface.logIn(database, login, password);
            if (currentUser == nullptr) {
                logowaniePoprawne = false;
                cout << "Wrong login or password\n";
                system("pause");
                system("cls");
               
            }
        } while (!logowaniePoprawne);
        cout << "You have succesfully logged in!\n";
        system("pause");
        system("cls");
        options();
    }
    else if (input == 2) {
        do {
            cout << "******REGISTER PAGE*******\n";
            cout << "login: ";
            cin >> login;
            cout << "\npassword: ";
            cin >> password;
        } while (!databaseInterface.registerUser(database, login, password));
        
    }
    else {
        cout << "Goodbye!";
    }
}
bool Interface::options() {
    cout << "User options:" << endl;
    cout << "1. Find Friends\n";
    cout << "2. Messege\n";
    cout << "3. Exit\n";
	int input = choice(3);
    switch (input) {
    case 1:
        cout << "Users list. Find your friend.\n";
        printUsers();
        break;

    case 2:
        cout << "Massege to your friend.\n";
        break;
    case 3:
        cout << "GoodBye!\n";
        break;
    }
    return true;
}
void Interface::printUsers() {
    int licznik = 1;
    int choiceuser; 
    
    for (auto user : database.getDatabase()) {
        if (user->getLogin() == currentUser->getLogin()) {
            continue;
        }
        cout << licznik << ". " << user->getLogin() << endl;
        licznik++;
    }
    choiceuser = this->choice(database.getDatabase().size());
    if (choiceuser == 0) return ;
    if (choiceuser >= 1 and choiceuser <= database.getDatabase().size()) {

    }
    

    
}