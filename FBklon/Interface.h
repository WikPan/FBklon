#pragma once
#include "LoginAndRegister.h"
#include "Messenger.h"
class Interface
{
protected:
	LoginAndRegister databaseInterface;
	Database database;
	shared_ptr<User> currentUser;
	Messenger messenger;
public:
	Interface();
	int startupScreen();
	bool options();		//Metoda wirtualna
	void printUsers(); //Metoda wirtualna
	void addUser();
	void addUserByLogin();
	int choice(int maxChoice);
	void checkAndAdd(shared_ptr<User> checked);


	LoginAndRegister getDatabaseInterface() { return this->databaseInterface; };
	Database getDatabase() { return this->database; };
	shared_ptr<User> getCurrentUser() { return this->currentUser; };
	Messenger getMessenger() { return this->messenger; };

	void deleteUserByIndex();
	void removeLineFromFile(const string& filename, const string& lineToRemove);
	void removeFolder(const string& usertodelatelogin);
	void removeFromFriends(const string& usertodelatelogin);
};

class AdminInterface : public Interface {
public:
	void printUsers();
	bool options();
	void deleteUserByIndex();
	AdminInterface& operator=(Interface& other) {
		databaseInterface = other.getDatabaseInterface();
		database = other.getDatabase();
		currentUser = other.getCurrentUser();
		messenger = other.getMessenger();
		return *this;
	}


	operator AdminInterface() const {
		
		return *this;
	}
};

