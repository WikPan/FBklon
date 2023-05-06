#pragma once
#include "LoginAndRegister.h"
#include "Messenger.h"
class Interface
{
private:
	LoginAndRegister databaseInterface;
	Database database;
	shared_ptr<User> currentUser;
	Messenger messenger;
public:
	Interface();
	void startupScreen();
	bool options();
	void printUsers();
	void addUser();
	void addUserByLogin();
	int choice(int maxChoice);
	void checkAndAdd(shared_ptr<User> checked);
};

class AdminInterface : public Interface {

};

