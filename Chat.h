#pragma once
#include <iostream>
#include "User.h"
#include <vector>


class Chat {

public:
	Chat();
	~Chat();
	

	User* regis(std::string& name, std::string& login, std::string& pasw);
	User* auth(std::string& login, std::string& pasw);

	void showUsers(User* user)const;
	void showChats(User* user);

	User* chatChoice(int number, User* me);

	User* userChoice(int number, User* me);
	void chatting(User* me, User* other);

	int chatSize()const;

private:
	
	std::vector<User*> _User;
};