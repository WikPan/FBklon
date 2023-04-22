#pragma once
#include <string>
using namespace std;

class User
{
private:
	string login;
	string password;
public:
	string getLogin() { return this->login; }
	string getPassword() { return this->password; }
	void setLogin(string& passedLogin) { this->login = passedLogin; }
	void setPassword(string& passedPassword) { this->password = passedPassword; }
	User(string loadedLogin, string loadedPassword): login(loadedLogin), password(loadedPassword) {}
	User() {}
};

class Friend : public User {
};

