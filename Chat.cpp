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


void Chat::acceptClient(){
	_Server->accepting();
}

void Chat::responseToClient(std::string &response){
	_Server->sendTo(response);
}

std::string Chat::commandFromClient(){
	return _Server->recFrom();
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
	std::string temp;
	char pasw2[LOGINLENGTH]{ 1 };
	temp = "Введите 0 для возврата на предыдущий экран или следуйте командам:\nВедите имя\n";
	_Server->sendTo(temp);
	temp.clear();
	name = _Server->recFrom();
	if (name[0] == '0' && name.size() == 1)
		return false;
	temp = "Введите логин\n";
	_Server->sendTo(temp);
	temp.clear();
	login = _Server->recFrom();
	if (login[0] == '0' && login.size() == 1)
		return false;
	temp = "Введите пароль\n";
	_Server->sendTo(temp);
	temp.clear();
	std::string tempPass = _Server->recFrom();
	for(int i = 0; i < tempPass.size(); i++){
		pasw[i] = tempPass[i];
	}
	if (pasw[0] == '0')
		if (!pasw[1])
			return false;
	temp = "Повторите пароль\n";
	_Server->sendTo(temp);
	temp.clear();
	tempPass.clear();
	tempPass = _Server->recFrom();
	for(int i = 0; i < tempPass.size(); i++){
		pasw2[i] = tempPass[i];
	}
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
	std::string temp;
	temp = "Введите 0 для возврата на предыдущий экран или следуйте командам:\nВведите логин\n";
	_Server->sendTo(temp);
	temp.clear();
	login = _Server->recFrom();
	if (login[0] == '0' && login.size() == 1)
		return false;
	temp = "Введите пароль\n";
	_Server->sendTo(temp);
	temp.clear();
	std::string tempPass = _Server->recFrom();
	for(int i = 0; i < tempPass.size(); i++){
		pasw[i] = tempPass[i];
	}
	std::cout << pasw[1];
	if (pasw[0] == '0')
		if (!pasw[1])
			return false;
	return true;
}

void Chat::showUsers(User* user) const
{
	std::string temp;
	clear_screen();
	int counter = 0;
	if (_User.size() > 1) {
		temp = "Выберите пользователя или введите 0 для возврата\n";
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() != user->getLog()) {
				counter++;
				temp += std::to_string(counter) + " " + _User[i]->getName() + "  |  " + _User[i]->getLog() + "\n";
				//std::cout << counter << " " << _User[i]->getName() << "  |  " << _User[i]->getLog() << "\n\n";
			}
		}
		_Server->sendTo(temp);
		temp.clear();
	}
	else
		temp = "Вы единственный пользователь :-(\n";
		_Server->sendTo(temp);
}

void Chat::showChats(User* user)
{
	std::string temp;
	clear_screen();
	if (!user->isEmptyMes()) {
		temp.clear();
		temp = "Введите номер диалога или 0 для возврата\n";
		temp += user->showAllChats();
		_Server->sendTo(temp);
		temp.clear();
	}
	else{
		temp = "Пока нет диалогов :-(\nНажмите Enter для возврата\n";
		//НАДО ПЕРЕДЕЛАТЬ!!!
		_Server->sendTo(temp);
	}
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
	clear_screen();
	std::string text;
	bool chattingStatus = true;
	while (chattingStatus) {
		text.clear();
		text = me->showOneChat(other);
		// _Server->sendTo(text);
		// text.clear();
		text += "\nВведите сообщение и нажмите Enter для отправки, для возврата отправьте 0\n";
		_Server->sendTo(text);
		text.clear();
		text = _Server->recFrom();
		if (text[0] == '0' && text.size() == 1) {
			chattingStatus = false;
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


