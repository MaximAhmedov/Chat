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
		std::cout << "Успешная регистрация!\n";
		return newUser;
	}
	else {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() == login) {
				std::cout << "Данный логин уже занят, попробуйте другой!\n";
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
	system("cls");
	uint* sh1 = sha1(pasw, LOGINLENGTH);
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			if (_User[i]->checkPass(sh1)) {
				std::cout << "Успешная авторизация!\n";
				return _User[i];
			}
			else {
				std::cout << "Неверный пароль!\n";
				return nullptr;
			}
		}
	}
	std::cout << "Данный пользователь не существует!\n";
	return nullptr;
}

bool Chat::regData(std::string& name, std::string& login, char pasw[], int paswLength)
{
	system("cls");
	char pasw2[LOGINLENGTH]{ 1 };
	std::cout << "Введите 0 для выхода на предыдущий экран выбора\n";
	std::cout << "Введите имя\n";
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
	system("cls");
	std::cout << "Введите 0 для выхода на предыдущий экран выбора\n";
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
		std::cout << "Вы единственный пользователь :-(\n";
}

void Chat::showChats(User* user)
{
	system("cls");
	if (!user->isEmptyMes()) {
		std::cout << "Выберите диалог или 0 чтобы вернутся на предыдущий экран\n";
		user->showAllChats();
	}
	else
		std::cout << "Пока нет начатых диалогов :-(\n";
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
	std::cout << "Введен неверный номер!\n";
	return nullptr;
}

void Chat::chatting(User* me, User* other)
{
	std::string text;
	bool chattingStatus = true;
	while (chattingStatus) {
		system("cls");
		me->showOneChat(other);
		std::cout << "\nВведите сообщение и нажмите Enter для отправки, для выхода из беседы отправьте 0\n";
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


