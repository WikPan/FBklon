#pragma once
#include "User.h"
#include <iostream>
#include <fstream>
class Database
{
private:
	list <shared_ptr<User>> database;

public:
	list<shared_ptr<User>> getDatabase() { return this->database; }
	void setDatabase(list<shared_ptr<User>> & passedDatabase) { this->database = passedDatabase; }
	bool loadDatabase(string fileName);
	void addUser(shared_ptr<User>& registered);
	void updateDatabaseInTXT();
	void addFriendFile(string addedFriendLogin, string currentUserLogin);
	void loadFriendsList(shared_ptr<User>& currentUser);
	void addUserFolder(shared_ptr<User>& currentUser);
	void createFriendFile(string friendLogin, string currentUserLogin);
	void clear();
};

