#include "Database.h"
#include <filesystem>


bool Database::loadDatabase(string fileName) {
    ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Couldn't open file called " << fileName << endl;
        return false;
	}
	else {
		string line;
        while (getline(file, line)) {
            size_t separatorPos = line.find(":");
            if (separatorPos == string::npos) {
                cout << "Improper line format " << line << endl;
                continue;
            }
            shared_ptr <User> userPtr = make_shared<User>(string(line.substr(0, separatorPos)), string(line.substr(separatorPos + 1)));
            this->database.push_back(userPtr);
        }
	}
    return true;
}
void Database::addUser(shared_ptr<User>& registered) {
    database.push_back(registered);
}
void Database::updateDatabaseInTXT() {
    ofstream file("Credentials.txt");
    for (auto user : database) {
        file << user->getLogin() << ":" << user->getPassword() << endl;
    }
    file.close();
}
void Database::addFriendFile(string addedFriendLogin, string currentUserLogin) {
    string userDirectory = "Users/" + currentUserLogin;
    string filePath = userDirectory + "/" + addedFriendLogin + ".txt";
    ofstream newFile(filePath.c_str());
    newFile.close();
}
void Database::createFriendFile(string friendLogin, string currentUserLogin) {
    string friendDirectory = "Users/" + friendLogin;
    string filePath = friendDirectory + "/" + currentUserLogin + ".txt";
    ofstream newFile(filePath);
    newFile.close();
}
void Database::loadFriendsList(shared_ptr<User>& currentUser) {
    string usersFolder = "Users/";
    string currentUserFolder = usersFolder + currentUser->getLogin();
    vector<string> friendsLogins;
    for (const auto& entry : filesystem::directory_iterator(currentUserFolder)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            friendsLogins.push_back(entry.path().stem().string());
        }
    }
    list<shared_ptr<User>> friendsList;
    for (auto& login : friendsLogins) {
        auto it = find_if(database.begin(), database.end(), [login](const auto& checkedFriendInList) {
            return login == checkedFriendInList->getLogin();
            });
        if (it != database.end()) {
            auto friendPtr = make_shared<User>(**it);
            friendsList.push_back(friendPtr);
        }
    }
    currentUser->setFriends(friendsList);
}
void Database::addUserFolder(shared_ptr<User>& currentUser) {
    string usersFolder = "Users/";
    if (!filesystem::is_directory(usersFolder)) {
        filesystem::create_directory(usersFolder);
    }


    string userFolder = usersFolder + currentUser->getLogin();
    if (!filesystem::is_directory(userFolder)) {
        filesystem::create_directory(userFolder);
    }
  
}
void Database::clear() {
    database.clear();
}
