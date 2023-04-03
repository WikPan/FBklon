#pragma once
#include "User.h"
#include <list>
#include <memory>
#include <iostream>
#include <fstream>
class Database
{
private:
	list <shared_ptr<User>> database;

public:
	list<shared_ptr<User>> getDatabase() { return this->database; }
	void setDatabase(list<shared_ptr<User>> passedDatabase) { this->database = passedDatabase; }
	bool loadDatabase();
};

