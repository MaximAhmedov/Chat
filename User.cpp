#include <iostream>
#include "User.h"

User::User(std::string& login, std::string& pasw) : _login(login), _pasw(pasw){
	_myMes = new HashTable;
}

User::User(std::string& name, std::string& login, std::string& pasw) : _name(name), _login (login), _pasw(pasw)
{
	_myMes = new HashTable;
}

User::~User()
{
	delete _myMes;
}

void User::setName(std::string& name)
{
	_name = name;
}

void User::setNewPas(std::string& oldPasw, std::string& newPasw)
{
	if (oldPasw == _pasw)
		_pasw = newPasw;
	else
		std::cout << "неверный пароль!\n";
}

std::string User::getName() const
{
	return this->_name;
}

std::string User::getLog() const
{
	return this->_login;
}

std::string User::getPasw() const
{
	return this->_pasw;
}

std::string User::getFriendNameInChat(int number)
{
	return _myMes->getNameHT(number);
}

void User::sendMes(std::string& text, User* sender, User* receiver)
{
	_myMes->send(text, receiver->getName());
	receiver->_myMes->getBy(text, sender->getName());
}

void User::showOneChat(User* mate) const
{
	system("cls");
	_myMes->showMessages(mate->getName());
}

void User::showAllChats() const
{
	_myMes->showMessWithAll();
}

bool User::isEmptyMes()
{
	return this->_myMes->isEmpty();
}


