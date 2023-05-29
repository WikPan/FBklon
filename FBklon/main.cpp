#include "Interface.h"
#include <chrono>
#include <time.h>
int main() {
	Interface myInter;
	int choice = myInter.startupScreen();
	if (choice == 1) {
		myInter.options();
	}
	else if (choice == 2) {
		shared_ptr<Interface> admInterface = make_shared<AdminInterface>();
		*admInterface = myInter;
		admInterface->options();
	}
	return 0;
}
