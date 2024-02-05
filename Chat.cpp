#include "Chat.h"

Chat::Chat()
{
}

Chat::~Chat()
{
	for (int i = 0; i < _User.size(); i++) {
		delete _User[i];
	}
}


User* Chat::regis(std::string& name, std::string& login, std::string& pasw)
{
	system("cls");
	User* newUser = nullptr;
	if (_User.empty()) {
		newUser = new User(name, login, pasw);
		_User.push_back(newUser);
		std::cout << "�������� �����������!\n";
		return newUser;
	}
	else {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() == login) {
				std::cout << "������ ����� ��� �����, ���������� ������!\n";
				return nullptr;
			}
			else {
				newUser = new User(name, login, pasw);
				_User.push_back(newUser);
				std::cout << "�������� �����������!\n";
				return newUser;
			}
		}
	}
	return nullptr;
}

User* Chat::auth(std::string& login, std::string& pasw)
{
	system("cls");
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			if (_User[i]->getPasw() == pasw) {
				std::cout << "�������� �����������!\n";
				return _User[i];
			}
			else {
				std::cout << "�������� ������!\n";
				return nullptr;
			}
		}
	}
	std::cout << "������ ������������ �� ����������!\n";
	return nullptr;
}

void Chat::showUsers(User* user) const
{
	system("cls");
	int counter = 0;
	if (_User.size() > 1) {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getName() != user->getName()) {
				counter++;
				std::cout << counter << " " << _User[i]->getName() << "\n";
			}
		}
	}
	else
		std::cout << "�� ������������ ������������ :-(\n";
}

void Chat::showChats(User* user)
{
	system("cls");
	if (!user->isEmptyMes()) {
		std::cout << "�������� ������ ��� 0 ����� �������� �� ���������� �����\n";
		user->showAllChats();
	}
	else
		std::cout << "���� ��� ������� �������� :-(\n";
}

User* Chat::chatChoice(int number, User* me)
{
	if (number < 1) {
		return nullptr;
	}
	std::string name = me->getFriendNameInChat(number);
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getName() == name) {
			return _User[i];
		}
	}
	return nullptr;
}

User* Chat::userChoice(int number, User* me)
{
	if (number < 1) {
		return nullptr;
	}
	int counter = 0;
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getName() != me->getName()) {
			counter++;
			if (counter == number) {
				return _User[i];
				
			}
		}
	}
	std::cout << "������ �������� �����!\n";
	return nullptr;
}

void Chat::chatting(User* me, User* other)
{
	std::string text;
	bool chattingStatus = true;
	std::cout << "������� ��������� � ������� Enter ��� ��������, ��� ������ �� ������ ��������� 0\n";
	while (chattingStatus) {
		std::getline(std::cin, text, '\n');
		if (text[0] == '0' && text.size() == 1) {
			chattingStatus = false;
			break;
		}
		else if (text.size() > 1) {   /*��������� �������!!!!*/
			me->sendMes(text, me, other);
		}
	}
}

int Chat::chatSize() const
{
	return _User.size();
}


