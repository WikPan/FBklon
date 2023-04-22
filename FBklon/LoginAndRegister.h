#pragma once
#include "Database.h"
class LoginAndRegister
{
public:
	shared_ptr<User> logIn(Database & databaseChecked, string& login, string& password);
	bool registerUser(Database& databaseChecked, string& login, string& password);

};

