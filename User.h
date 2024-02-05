#pragma once
#include <iostream>
#include <string>
#include "MessageHT.h"

class User {
public:
	User(std::string& login, std::string& pasw);
	User(std::string& name, std::string& login, std::string& pasw);
	~User();
	void setName(std::string& name);
	void setNewPas(std::string& oldPasw, std::string& newPasw);

	std::string getName()const;
	std::string getLog()const;
	std::string getPasw()const;

	std::string getFriendNameInChat(int number);

	void sendMes(std::string& text, User* sender, User* receiver);
	void showOneChat(User* mate)const;
	void showAllChats()const;

	bool isEmptyMes();

private:
	HashTable* _myMes;
	std::string _name;
	std::string _login;
	std::string _pasw;

};