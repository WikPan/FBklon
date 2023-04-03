#include "LoginAndRegister.h"

shared_ptr<User> LoginAndRegister::logIn(Database& databaseChecked, string & login, string & password) {
	for (auto& user : databaseChecked.getDatabase()) {
		if (user->getLogin() == login && user->getPassword() == password)
			return user;
	}
	return nullptr;
}
