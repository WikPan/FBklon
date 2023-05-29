#pragma once
#include "LoginAndRegister.h"
#include "Messenger.h"

class Interface
{
protected:
    LoginAndRegister databaseInterface;
    Database usersDatabase;
    Database adminsDatabase;
    shared_ptr<User> currentUser;
    Messenger messenger;

public:
    Interface();
    int startupScreen();
    virtual bool options();
    void printUsers(); 
    void addUser();
    void addUserByLogin();
    int choice(int maxChoice);
    void checkAndAdd(shared_ptr<User> checked);

    LoginAndRegister getDatabaseInterface() { return this->databaseInterface; };
    Database getDatabase() { return this->usersDatabase; };
    Database getAdminDatabase() { return this->adminsDatabase; };
    shared_ptr<User> getCurrentUser() { return this->currentUser; };
    Messenger getMessenger() { return this->messenger; };
};

class AdminInterface : public Interface {
public:
    bool options() override;     
    AdminInterface& operator=(Interface& other) {
        databaseInterface = other.getDatabaseInterface();
        usersDatabase = other.getDatabase();
        currentUser = other.getCurrentUser();
        messenger = other.getMessenger();
        return *this;
    }
    void deleteUserByIndex();
    void removeLineFromFile(const string& filename, const string& lineToRemove);
    void removeFolder(const string& usertodelatelogin);
    void removeFromFriends(const string& usertodelatelogin);
   
};
