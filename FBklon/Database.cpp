#include "Database.h"

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
            unique_ptr <User> userPtr = make_unique<User>(line.substr(0, separatorPos), line.substr(separatorPos + 1));
            this->database.push_back(userPtr);
        }
	}
    return true;
}
