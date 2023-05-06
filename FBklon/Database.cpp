#include "Database.h"
#include <filesystem>


bool Database::loadDatabase() {
	ifstream file("Credentials.txt");
	if (!file.is_open()) {
		cout << "Nie mo¿na otworzyæ pliku Credentials.txt" << endl;
        return false;
	}
	else {
		string line;
        while (getline(file, line)) {
            size_t separatorPos = line.find(":");
            if (separatorPos == string::npos) {
                cerr << "Nieprawid³owy format w linii: " << line << endl;
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

    // Utwórz œcie¿kê do pliku
    string filePath = userDirectory + "/" + addedFriendLogin + ".txt";

    // Utwórz plik tekstowy o podanej nazwie
    ofstream newFile(filePath.c_str());
    // Zamknij plik
    newFile.close();
}
void Database::loadFriendsList(shared_ptr<User>& currentUser) {

    // Tworzenie œcie¿ki do folderu "Users"
    string usersFolder = "Users/";

    // Tworzenie œcie¿ki do folderu bie¿¹cego u¿ytkownika
    string currentUserFolder = usersFolder + currentUser->getLogin();

    // Pobieranie nazw plików z rozszerzeniem ".txt" z folderu bie¿¹cego u¿ytkownika
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
    // Tworzenie œcie¿ki do folderu "Users"
    string usersFolder = "Users/";

    // Sprawdzenie, czy folder istnieje i utworzenie go, jeœli nie
    if (!filesystem::is_directory(usersFolder)) {
        filesystem::create_directory(usersFolder);
    }

    // Dodanie folderu u¿ytkownika
    string userFolder = usersFolder + currentUser->getLogin();
    if (!filesystem::is_directory(userFolder)) {
        filesystem::create_directory(userFolder);
    }
    //Gdy rejestrujemy nowego uzytkownika to tworzymy jego folder w folderze Users.
    // 
    //Dziêki temu gdy nowy uzytkownik bêdzie chcial rozmawiac z innym, to w tym jego podfolderze zostanie utworzony plik tekstowy 
}