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


User* Chat::regis(std::string& name, std::string& login, char pasw[], int paswLength)
{
	system("cls");

	uint* sh1 = sha1(pasw, LOGINLENGTH);
	User* newUser = nullptr;
	if (_User.empty()) {
		newUser = new User(name, login, sh1);
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
				newUser = new User(name, login, sh1);
				_User.push_back(newUser);
				std::cout << "�������� �����������!\n";
				return newUser;
			}
		}
	}
	return nullptr;
}

User* Chat::auth(std::string& login, char pasw[], int paswLength)
{
	system("cls");
	uint* sh1 = sha1(pasw, LOGINLENGTH);
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			if (_User[i]->checkPass(sh1)) {
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

bool Chat::regData(std::string& name, std::string& login, char pasw[], int paswLength)
{
	system("cls");
	char pasw2[LOGINLENGTH]{ 1 };
	std::cout << "������� 0 ��� ������ �� ���������� ����� ������\n";
	std::cout << "������� ���\n";
	std::cin >> name;
	if (name[0] == '0' && name.size() == 1)
		return false;
	std::cout << "������� �����\n";
	std::cin >> login;
	if (login[0] == '0' && login.size() == 1)
		return false;
	std::cout << "������� ������\n";
	std::cin >> pasw;
	if (pasw[0] == '0')
		if (!pasw[1])
			return false;
	std::cout << "��������� ������\n";
	std::cin >> pasw2;
	if (pasw2[0] == '0')
		if (!pasw2[1])
			return false;
	else if (strcmp(pasw, pasw2))
		return false;

	return true;
}

bool Chat::authData(std::string& login, char pasw[])
{
	system("cls");
	std::cout << "������� 0 ��� ������ �� ���������� ����� ������\n";
	std::cout << "������� �����\n";
	std::cin >> login;
	if (login[0] == '0' && login.size() == 1)
		return false;
	std::cout << "������� ������\n";
	std::cin >> pasw;
	std::cout << pasw[1];
	if (pasw[0] == '0')
		if (!pasw[1])
			return false;
	return true;
}

void Chat::showUsers(User* user) const
{
	system("cls");
	int counter = 0;
	if (_User.size() > 1) {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() != user->getLog()) {
				counter++;
				std::cout << counter << " " << _User[i]->getName() << "  |  " << _User[i]->getLog() << "\n\n";
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
	std::string login = me->getFriendLogInChat(number);
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
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
		if (_User[i]->getLog() != me->getLog()) {
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
	while (chattingStatus) {
		system("cls");
		me->showOneChat(other);
		std::cout << "\n������� ��������� � ������� Enter ��� ��������, ��� ������ �� ������ ��������� 0\n";
		std::getline(std::cin, text, '\n');
		if (text[0] == '0' && text.size() == 1) {
			chattingStatus = false;
			system("cls");
			break;
		}
		else if (text.size() > 1) {
			me->sendMes(text, me, other);
		}
	}
}

int Chat::chatSize() const
{
	return _User.size();
}


