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
				newUser = new User(name, login, pasw);
				_User.push_back(newUser);
				std::cout << "Успешная регистрация!\n";
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
	std::cout << "Введен неверный номер!\n";
	return nullptr;
}

void Chat::chatting(User* me, User* other)
{
	std::string text;
	bool chattingStatus = true;
	std::cout << "Введите сообщение и нажмите Enter для отправки, для выхода из беседы отправьте 0\n";
	while (chattingStatus) {
		std::getline(std::cin, text, '\n');
		if (text[0] == '0' && text.size() == 1) {
			chattingStatus = false;
			break;
		}
		else if (text.size() > 1) {   /*исправить условие!!!!*/
			me->sendMes(text, me, other);
		}
	}
}

int Chat::chatSize() const
{
	return _User.size();
}


