#include "Database.h"

bool Database::loadDatabase() {
	ifstream file("Credentials.txt");
	if (!file.is_open()) {
		cout << "Nie mo�na otworzy� pliku Credentials.txt" << endl;
        return false;
	}
	else {
		string line;
        while (getline(file, line)) {
            size_t separatorPos = line.find(":");
            if (separatorPos == string::npos) {
                cerr << "Nieprawid�owy format w linii: " << line << endl;
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

    // Utw�rz �cie�k� do pliku
    string filePath = userDirectory + "/" + addedFriendLogin + ".txt";

    // Utw�rz plik tekstowy o podanej nazwie
    ofstream newFile(filePath.c_str());
    // Zamknij plik
    newFile.close();
}
void Database::loadFriendsList(shared_ptr<User> & currentUser) {

}
void Database::addUserFolder(shared_ptr<User>& currentUser) {
   
}