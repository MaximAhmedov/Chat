#pragma once
#include <iostream>
#include <string>
#include "MessageHT.h"
#include "Sha1.h"



class User {
public:
	User(std::string& login, uint* pass);
	User(std::string& name, std::string& login, uint* pass);
	~User();
	void setName(std::string& name);

	std::string getName()const;
	std::string getLog()const;
	bool checkPass(uint* pass) const;

	std::string getFriendLogInChat(int number);

	void sendMes(std::string& text, User* sender, User* receiver);
	void showOneChat(User* mate)const;
	void showAllChats()const;

	bool isEmptyMes();

private:
	HashTable* _myMes;
	std::string _name;
	std::string _login;
	uint* _pass;

};