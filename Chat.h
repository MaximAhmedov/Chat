#pragma once
#include <iostream>
#include "User.h"
#include "Sha1.h"
#include <vector>

#define LOGINLENGTH 10

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() clear
#endif

class Chat {

public:
	Chat();
	~Chat();
	

	User* regis(std::string& name, std::string& login, char pasw[], int paswLength);
	User* auth(std::string& login, char pasw[], int paswLength);
	bool regData(std::string& name, std::string& login, char pasw[], int paswLength);
	bool authData(std::string& login, char pasw[]);

	void showUsers(User* user)const;
	void showChats(User* user);

	User* chatChoice(int number, User* me);

	User* userChoice(int number, User* me);
	void chatting(User* me, User* other);

	int chatSize()const;

private:
	
	std::vector<User*> _User;
};