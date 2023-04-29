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
            cout << "******REGISTER PAGE******\n";
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
    cout << "1. View users.\n";
    cout << "2. Find user by login.\n";
    cout << "3. Message.\n";
    cout << "4. Exit.\n";
	int input = choice(4);
    switch (input) {
    case 1:
        addUser();
        break;
    case 2:
        addUserByLogin();
        break;
    case 3:
        cout << "Message your friend.\n";
        break;
    case 4:
        cout << "Goodbye!\n";
        break;
    }
    return true;
}
void Interface::printUsers(){
    int counter = 1;
        for (auto user : database.getDatabase()) {
            if (user->getLogin() == currentUser->getLogin())
                continue;
        cout << counter << ". " << user->getLogin() << endl;
        counter++;
    }
}
void Interface::checkAndAdd(shared_ptr<User> checked) {
    if (currentUser->addFriend(checked))
        database.addFriendFile(checked->getLogin(), currentUser->getLogin());
    else {
        cout << "You are already friends...\n";
        system("pause");
        system("cls");
    }
}
void Interface::addUser() {
    int userIndex;
    bool correct = false;
    do {
        cout << "Users list. Find your friend.\n";
        printUsers();
        cout << "Select user to add them to your friends list.\nIf you want to exit this panel enter 0:\n";
        cin >> userIndex;
        if (userIndex == 0) 
            return;
        if (userIndex >= 1 and userIndex <= database.getDatabase().size()-1) {
            correct = true;
            int counter = 1;
            for (auto user : database.getDatabase()) {
                if (counter == userIndex) {
                    checkAndAdd(user);
                }
                counter++;
            }
        }
        else {
            correct = false;
            cout << "Wrong option! Please make sure to choose option from range <0;" << database.getDatabase().size() - 1 << ">\n";
            system("pause");
            system("cls");
        }
    } while (!correct);  

}
void Interface::addUserByLogin() {
    string login;
    cout << "Please input your friend login in order to add them (Enter 0 to exit):\n";
    cin >> login;
    bool correct = false;
    if (login == "0")
        return;
    for (auto user : database.getDatabase()) {
        if (user->getLogin() == login) {
            cout << "We found your friend!\n";
            checkAndAdd(user);
            correct = true;
        }
        
    }
    if(!correct){
        cout << "We didnt found your friend.\n";
        system("PAUSE");
        system("CLS");
    }

}