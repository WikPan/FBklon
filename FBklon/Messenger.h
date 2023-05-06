#pragma once
#include <chrono>
#include <time.h>
#include "Database.h"
class Messenger
{
public:
	string printTime();
	void message(shared_ptr<User>& currentUser);
	void printFriends(list<shared_ptr<User>> friends);
	filesystem::path chooseFriend(shared_ptr<User>& currentUser);
};

