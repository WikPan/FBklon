#pragma once
#include <string>
#include <memory>
#include <list>
using namespace std;

class User
{
private:
	string login;
	string password;
	list <shared_ptr<User>> friends;
public:
	bool addFriend(shared_ptr<User> newFriend);
	string getLogin() { return this->login; }
	string getPassword() { return this->password; }
	list <shared_ptr<User>> getFriends() { return this->friends; }
	void setFriends(list <shared_ptr<User>> newFriendsList) { this->friends = newFriendsList; }
	void setLogin(string& passedLogin) { this->login = passedLogin; }
	void setPassword(string& passedPassword) { this->password = passedPassword; }
	User(string loadedLogin, string loadedPassword): login(loadedLogin), password(loadedPassword) {}
	User() {}
};

class Friend : public User {
};

