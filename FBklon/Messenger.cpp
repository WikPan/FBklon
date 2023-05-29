#include "Messenger.h"

string Messenger::printTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	
	std::tm local_now;
	localtime_s(&local_now, &now_c);


	int year = local_now.tm_year + 1900; // rok (od 1900)
	int month = local_now.tm_mon + 1; // miesi¹c (od 0 do 11)
	int day = local_now.tm_mday; // dzieñ miesi¹ca
	int hour = local_now.tm_hour; // godzina (od 0 do 23)
	int min = local_now.tm_min; // minuta (od 0 do 59)
	string abc = "[" + to_string(hour) + ":" + to_string(min) + "-" + to_string(day) + "." + to_string(month) + "." + to_string(year) + "]";
	return abc;
}
Paths Messenger::chooseFriend(shared_ptr<User>& currentUser, bool & exitChoosing) {
    filesystem::path currentUserFolder = filesystem::current_path() / "Users" ;
    int userIndex;
    bool correct = false;
    Paths paths;
    do {
        cout << "Friend list. Who you want to messege.\n";
        printFriends(currentUser->getFriends());
        cout << "Select user to message your friends list.\nIf you want to exit this panel enter 0:\n";
        cin >> userIndex;
        if (userIndex == 0) {
            exitChoosing = true;
            return paths;
        }
           
        if (userIndex >= 1 and userIndex <= currentUser->getFriends().size()) {
            correct = true;
            int counter = 1;
            for (auto user : currentUser->getFriends()) {
                if (counter == userIndex) {
                    string login = user->getLogin();
                    paths.first = currentUserFolder/ currentUser->getLogin() / (login + ".txt");
                    paths.second = currentUserFolder / (login) / (currentUser->getLogin()+".txt");
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
    return paths;
}
void Messenger::PrintFile(filesystem::path& filePath) {
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}
void Messenger::printFriends(list<shared_ptr<User>> friends) {
    int counter = 1;
    for (auto& user : friends) {
        cout << counter << ". " << user->getLogin() << endl;
        counter++;
    }
}
void Messenger::message(shared_ptr<User>& currentUser) {
    bool exit = false;
    Paths userPathAndFriendPath = chooseFriend(currentUser, exit);
    while(!exit){
        PrintFile(userPathAndFriendPath.first);
        string message;
        cout << "Enter message: ";
        cin.ignore();
        getline(cin, message);
        ofstream outfile(userPathAndFriendPath.first, ios::app);
        if (outfile.is_open()) {
            outfile << printTime() << " " << currentUser->getLogin() << ": " << message << endl;
            outfile.close();
            UpdateFriendsFile(userPathAndFriendPath.second, currentUser->getLogin(), message);
            int choice;
            cout << "Message sent! Would you like to write another one? (1. Yes/2. No): \n";
            cin >> choice;
            if (choice == 1)
                system("cls");
            else {
                exit = true;
                system("cls");
            }
        }
        else {
            cout << "Couldn't open file!" << endl;
            return;
        }
    };
}
void Messenger::UpdateFriendsFile(filesystem::path& ToFriendFilePath, string currentUserLogin, string & message) {
    ofstream outfile(ToFriendFilePath, ios::app);
    if (outfile.is_open()) {
        outfile << printTime() << " " << currentUserLogin << ": " << message << endl;
        outfile.close();
    }
    else {
        cout << "Couldn't open file!" << endl;
        return;
    }
}


