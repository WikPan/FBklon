#include "User.h"
bool User::addFriend(shared_ptr<User> newFriend) {
	auto it = find_if(friends.begin(), friends.end(), [newFriend](const auto& checkedFriendInList) {
		return checkedFriendInList->getLogin() == newFriend->getLogin();
		});
	if (it == friends.end()) {
		this->friends.push_back(newFriend);
		return true;
	}
	else
		return false;
}