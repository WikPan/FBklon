#include "Interface.h"

Interface::Interface() {
	usersDatabase.loadDatabase("Credentials.txt");
	adminsDatabase.loadDatabase("AdminCredentials.txt");
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

int Interface::startupScreen() {

	cout << "Welcome to BookFace?\n";
	cout << "1. Login\n";
	cout << "2. Register\n";
	cout << "3. Admin Login\n";
	cout << "4. Exit\n";
	string login, password;

	int input = choice(4);
	if (input == 1) {
		bool loggedIn = true;
		do {
			loggedIn = true;
			cout << "*****LOGIN PAGE*****\n";
			cout << "Login: ";
			cin >> login;
			cout << "Password: ";
			cin >> password;
			currentUser = databaseInterface.logIn(usersDatabase, login, password);
			if (currentUser == nullptr) {
				loggedIn = false;
				cout << "Wrong login or password\n";
				system("pause");
				system("cls");

			}
		} while (!loggedIn);
		cout << "You have succesfully logged in!\n";
		system("pause");
		system("cls");
		return 1;
	}
	else if (input == 2) {
		do {
			system("cls");
			cout << "******REGISTER PAGE******\n";
			cout << "login: ";
			cin >> login;
			cout << "\npassword: ";
			cin >> password;
		} while (!databaseInterface.registerUser(usersDatabase, login, password));
		currentUser = databaseInterface.logIn(usersDatabase, login, password);
		system("cls");
		return 1;
	}
	else if (input == 3) {
		bool loggedIn = true;
		do {
			loggedIn = true;
			cout << "*****LOGIN ADMIN PAGE*****\n";
			cout << "Login: ";
			cin >> login;
			cout << "Password: ";
			cin >> password;
			currentUser = databaseInterface.logIn(adminsDatabase, login, password);
			if (currentUser == nullptr) {
				loggedIn = false;
				cout << "Wrong login or password\n";
				system("pause");
				system("cls");

			}
		} while (!loggedIn);

		cout << "You have succesfully logged in!\n";
		system("pause");
		system("cls");
		return 2;
	}
	else {
		cout << "Goodbye!";
		return 3;
	}
}
bool Interface::options() {
	usersDatabase.loadFriendsList(currentUser);
	bool exitD = false;
	while (!exitD) {
		cout << "User options:" << endl;
		cout << "1. Add users.\n";
		cout << "2. Add user by login.\n";
		cout << "3. Message.\n";
		cout << "4. Exit.\n";
		int input = choice(4);
		switch (input) {
		case 1:
			system("cls");
			addUser();
			break;
		case 2:
			addUserByLogin();
			break;
		case 3:
			cout << "Message your friend.\n";
			messenger.message(currentUser);
			break;
		case 4:
			cout << "Goodbye!\n";
			exitD = true;
			break;
		}
	}
	return true;
}
bool AdminInterface::options() {
	bool exitD = false;
	while (!exitD) {
		cout << "User options:" << endl;
		cout << "1. View users.\n";
		cout << "2. Delete users.\n";
		cout << "3. Exit.\n";
		int input = choice(3);
		switch (input) {
		case 1:
			system("cls");
			printUsers();
			system("pause");
			system("cls");
			break;
		case 2:
			deleteUserByIndex();
			system("cls");
			break;
		case 3:
			cout << "Goodbye!\n";
			exitD = true;
			break;
		}
	}
	return true;
}
void Interface::printUsers() {
	int counter = 1;
	for (auto user : usersDatabase.getDatabase()) {
		if (user->getLogin() == currentUser->getLogin())
			continue;
		cout << counter << ". " << user->getLogin() << endl;
		counter++;
	}
}

void Interface::checkAndAdd(shared_ptr<User> checked) {
	if (currentUser->addFriend(checked)) {
		usersDatabase.addFriendFile(checked->getLogin(), currentUser->getLogin());
		usersDatabase.createFriendFile(checked->getLogin(), currentUser->getLogin());
	}
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
		if (userIndex >= 1 and userIndex <= usersDatabase.getDatabase().size() - 1) {
			correct = true;
			int counter = 1;
			for (auto user : usersDatabase.getDatabase()) {
				if (counter == userIndex) {
					checkAndAdd(user);
				}
				counter++;
			}
		}
		else {
			correct = false;
			cout << "Wrong option! Please make sure to choose option from range <0;" << usersDatabase.getDatabase().size() - 1 << ">\n";
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
	for (auto user : usersDatabase.getDatabase()) {
		if (user->getLogin() == login) {
			cout << "We found your friend!\n";
			checkAndAdd(user);
			correct = true;
		}
	}
	if (!correct) {
		cout << "We didnt found your friend.\n";
		system("PAUSE");
		system("CLS");
	}
}
void AdminInterface::deleteUserByIndex()
{
	bool correct = false;
	int index;
	do {
		cout << "Users list. \n";
		printUsers();
		cout << "Select user to delete them.\nIf you want to exit this panel enter 0:\n";
		cin >> index;
		if (index == 0)
			return;
		if (index >= 1 and index <= usersDatabase.getDatabase().size()) {
			correct = true;
			int counter = 1;
			auto databaseData = usersDatabase.getDatabase();
			for (auto user : databaseData) {
				if (user->getLogin() == currentUser->getLogin())
					continue;
				if (counter == index) {
					string lineToRemove = user->getLogin() + ":" + user->getPassword();
					removeLineFromFile("Credentials.txt", lineToRemove);
					removeFolder(user->getLogin());
					removeFromFriends(user->getLogin());
				}
				if (!(user->getLogin() == currentUser->getLogin()))
					counter++;
			}
		}
		else {
			correct = false;
			cout << "Wrong option! Please make sure to choose option from range <0;" << usersDatabase.getDatabase().size() << ">\n";
			system("pause");
			system("cls");
		}
	} while (!correct);
	usersDatabase.clear();
	usersDatabase.loadDatabase("Credentials.txt");
}
void AdminInterface::removeLineFromFile(const string& filename, const string& lineToRemove)
{
	ifstream inputFile(filename);
	ofstream tempFile("temp.txt");

	if (inputFile.is_open() && tempFile.is_open()) {
		string line;
		while (getline(inputFile, line)) {
			if (line != lineToRemove) {
				tempFile << line << endl;
			}
		}
		inputFile.close();
		tempFile.close();
		remove(filename.c_str());
		if (rename("temp.txt", filename.c_str()) != 0) {
			cout << "Failed to rename the file.\n";
		}
	}
	else {
		cout << "Error opening files.\n";
	}
}

void AdminInterface::removeFolder(const string& usertodelatelogin) {
	filesystem::path userFolderPath = filesystem::current_path() / "Users" / usertodelatelogin;
	if (!filesystem::exists(userFolderPath)) {
		cout << "User folder does not exist for " << usertodelatelogin << ".\n";
		return;
	}
	filesystem::remove_all(userFolderPath);
}
void AdminInterface::removeFromFriends(const string& userLoginToDelete) {
	for (auto& user : usersDatabase.getDatabase()) {
		if (user->getLogin() != userLoginToDelete) {
			filesystem::path friendFolderPath = filesystem::current_path() / "Users" / user->getLogin();
			for (const auto& entry : filesystem::directory_iterator(friendFolderPath))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".txt" && entry.path().stem() == userLoginToDelete)
				{
					filesystem::remove(entry.path());
					cout << "File " << entry.path().filename() << " has been deleted.\n";
					return;
				}
			}
		}
	}
}