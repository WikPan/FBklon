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
	void startupScreen();
	bool options();
	void printUsers();
	/** \brief Funkcja pobieraj�ca liczb� od u�ytkownika dop�ki wyb�r nie nale�y do zakresu <1;maxChoice>.
	* \param[in] maxChoice Maksymalna mo�liwa opcja 
	*/
	int choice(int maxChoice);
};

class AdminInterface : public Interface {

};

