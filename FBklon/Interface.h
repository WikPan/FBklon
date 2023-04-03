#pragma once
#include "LoginAndRegister.h"
class Interface
{
private:
	LoginAndRegister databaseInterface;
	Database database;
	shared_ptr<User> currentUser;
public:
	Interface();
	bool startupScreen();
	bool options();
	int choice(int maxChoice);
};

