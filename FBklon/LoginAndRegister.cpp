#include "LoginAndRegister.h"

shared_ptr<User> LoginAndRegister::logIn(Database& databaseChecked, string & login, string & password) {
	for (auto& user : databaseChecked.getDatabase()) {
		if (user->getLogin() == login && user->getPassword() == password) {
			return user;
		}
	}
	return nullptr;
}
bool LoginAndRegister::registerUser(Database& databaseChecked, string& login, string& password) {
	for (auto user : databaseChecked.getDatabase()) {
		if (user->getLogin() == login) {
			cout << "This login is already used! Please try another one...\n";
			
			system("pause");
			system("cls");
			return false;
		}	
	}
	shared_ptr<User> createdUser = make_shared <User>(login, password);
	databaseChecked.addUser(createdUser);
	databaseChecked.addUserFolder(createdUser);
	databaseChecked.updateDatabaseInTXT();
	return true;
}
shared_ptr<User> LoginAndRegister::logInAdmin(Database& databaseChecked, string& login, string& password) {
	for (auto& user : databaseChecked.getDatabase()) {
		if (user->getLogin() == login && user->getPassword() == password) {
			return user;
		}
	}
	return nullptr;
}