#include "Messenger.h"
#include <filesystem>
string Messenger::printTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	// Konwersja czasu i daty na reprezentacjê lokaln¹
	std::tm local_now;
	localtime_s(&local_now, &now_c);

	// Pobranie poszczególnych elementów czasu i daty
	int year = local_now.tm_year + 1900; // rok (od 1900)
	int month = local_now.tm_mon + 1; // miesi¹c (od 0 do 11)
	int day = local_now.tm_mday; // dzieñ miesi¹ca
	int hour = local_now.tm_hour; // godzina (od 0 do 23)
	int min = local_now.tm_min; // minuta (od 0 do 59)
	string abc = "[" + to_string(hour) + ":" + to_string(min) + "-" + to_string(day) + "." + to_string(month) + "." + to_string(year) + "]";
	return abc;
}
void Messenger::message(shared_ptr<User>& currentUser) {
   
    filesystem::path currentUserFolder = filesystem::current_path() / "users" / currentUser->getLogin();
    int userIndex;
    bool correct = false;
    filesystem::path filePath;
    do {
        cout << "Friend list. Who you want to messege.\n";
        printFriends(currentUser->getFriends());
        cout << "Select user to messege your friends list.\nIf you want to exit this panel enter 0:\n";
        cin >> userIndex;
        if (userIndex == 0)
            return;
        if (userIndex >= 1 and userIndex <= currentUser->getFriends().size()) {
            correct = true;
            int counter = 1;
            for (auto user : currentUser->getFriends()) {
                if (counter == userIndex) {
                    string login = user->getLogin();
                    filePath = currentUserFolder / (login + ".txt");
                }
                counter++;
            }
        }
        else {
            correct = false;
            cout << "Wrong option! Please make sure to choose option from range <0;" << currentUser->getFriends().size() << ">\n";
            system("pause");
            system("cls");
        }
    } while (!correct);

    
    bool continueTexting = false;
    do {
        ifstream file(filePath);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        string message;
        cout << "Enter message: ";
        cin.ignore();
        getline(cin, message);
        ofstream outfile(filePath, ios::app);
        if (outfile.is_open()) {
            outfile << printTime() << " " << currentUser->getLogin() << ": " << message << endl;
            outfile.close();
            int choice;
            cout << "Message sent! Would you like to write another one? (1. Yes/2. No): \n";
            cin >> choice;
            if (choice == 1) {
                continueTexting = true;
                system("cls");
            }
            else {
                continueTexting = false;
                system("cls");
            }
        }
        else {
            cout << "Couldn't open file!" << std::endl;
            return;
        }
    } while (continueTexting);
}
void Messenger::printFriends(list<shared_ptr<User>> friends) {
    int counter = 1;
    for (auto& user : friends) {
        cout << counter << ". " << user->getLogin() << endl;
        counter++;
    }
