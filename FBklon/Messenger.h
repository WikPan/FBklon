#pragma once
#include <chrono>
#include <time.h>
#include <filesystem>
#include "Database.h"
struct Paths {
	filesystem::path first;
	filesystem::path second;
};
class Messenger
{
public:
	string printTime();
	void message(shared_ptr<User>& currentUser);
	void printFriends(list<shared_ptr<User>> friends);
	Paths chooseFriend(shared_ptr<User>& currentUser, bool& exitChoosing);
	void UpdateFriendsFile(filesystem::path & ToFriendFilePath, string currentUserLogin, string & message);
	void PrintFile(filesystem::path & filePath);
};
	

