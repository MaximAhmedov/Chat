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
	clear_screen();

	uint* sh1 = sha1(pasw, LOGINLENGTH);
	User* newUser = nullptr;
	if (_User.empty()) {
		newUser = new User(name, login, sh1);
		_User.push_back(newUser);
		std::cout << "Успешная регистрация!\n";
		return newUser;
	}
	else {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() == login) {
				std::cout << "Логин занят, попробуйте другой!\n";
				return nullptr;
			}
			else {
				newUser = new User(name, login, sh1);
				_User.push_back(newUser);
				std::cout << "Успешная регистрация!\n";
				return newUser;
			}
		}
	}
	return nullptr;
}

User* Chat::auth(std::string& login, char pasw[], int paswLength)
{
	clear_screen();
	uint* sh1 = sha1(pasw, LOGINLENGTH);
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			if (_User[i]->checkPass(sh1)) {
				std::cout << "успешная авторизация!\n";
				return _User[i];
			}
			else {
				std::cout << "неверный пароль!\n";
				return nullptr;
			}
		}
	}
	std::cout << "Пользователя с данным логином не существует!\n";
	return nullptr;
}

bool Chat::regData(std::string& name, std::string& login, char pasw[], int paswLength)
{
	clear_screen();
	char pasw2[LOGINLENGTH]{ 1 };
	std::cout << "Введите 0 для возврата на предыдущий экран или следуйте командам:\n";
	std::cout << "Ведите имя\n";
	std::cin >> name;
	if (name[0] == '0' && name.size() == 1)
		return false;
	std::cout << "Введите логин\n";
	std::cin >> login;
	if (login[0] == '0' && login.size() == 1)
		return false;
	std::cout << "Введите пароль\n";
	std::cin >> pasw;
	if (pasw[0] == '0')
		if (!pasw[1])
			return false;
	std::cout << "Повторите пароль\n";
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
	clear_screen();
	std::cout << "Введите 0 для возврата на предыдущий экран или следуйте командам:\n";
	std::cout << "Введите логин\n";
	std::cin >> login;
	if (login[0] == '0' && login.size() == 1)
		return false;
	std::cout << "Введите пароль\n";
	std::cin >> pasw;
	std::cout << pasw[1];
	if (pasw[0] == '0')
		if (!pasw[1])
			return false;
	return true;
}

void Chat::showUsers(User* user) const
{
	clear_screen();
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
		std::cout << "Вы единственный пользователь :-(\n";
}

void Chat::showChats(User* user)
{
	clear_screen();
	if (!user->isEmptyMes()) {
		std::cout << "Введите номер диалога или 0 для возврата\n";
		user->showAllChats();
	}
	else
		std::cout << "Пока нет диалогов :-(\n";
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
	std::cout << "Ошибка!\n";
	return nullptr;
}

void Chat::chatting(User* me, User* other)
{
	std::string text;
	bool chattingStatus = true;
	while (chattingStatus) {
		clear_screen();
		me->showOneChat(other);
		std::cout << "\nВведите сообщение и нажмите Enter для отправки, для возврата отправьте 0\n";
		std::getline(std::cin, text, '\n');
		if (text[0] == '0' && text.size() == 1) {
			chattingStatus = false;
			clear_screen();
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


