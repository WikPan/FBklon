#pragma once
#include "User.h"
#include <list>
#include <memory>
#include <iostream>
#include <fstream>
class Database
{
private:
	list <unique_ptr<User>> database;

public:
	list<unique_ptr<User>> getDatabase() { return this->database; }
	void setDatabase(list<unique_ptr<User>> passedDatabase) { this->database = passedDatabase; }
	bool loadDatabase();
};

