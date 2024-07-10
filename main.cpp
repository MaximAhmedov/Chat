#include <iostream>
#include <algorithm>
//#include "Chat.h"
#include "myServer.h"


#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

int main() {
	
	//Chat chat;
	myServer server;
	//User* me = nullptr;
	//User* other = nullptr;
	
	server.fdStart();
	while(true){
		int counter = server.selectFunc();
		for(int i = 0; i < counter; i++){
			server.mainFunc(i);
		}

	}
	return 0;
}