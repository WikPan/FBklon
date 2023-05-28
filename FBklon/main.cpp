#include "Interface.h"
#include <chrono>
#include <time.h>

int main() {
	Interface myInter;
	int choice = myInter.startupScreen();
	if (choice==1) {
		myInter.options();
	}
	else if (choice == 2) {
		AdminInterface admInterface;
		admInterface = myInter;
		admInterface.options();
	
		
	}
	else {
		
	}
	



}