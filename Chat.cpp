#include "Chat.h"
Chat::Chat()
{
	comMap["REGIS"] = COMMAND::REGIS;
	comMap["SIGNIN"] = COMMAND::SIGNIN;
	comMap["CHATW"] = COMMAND::CHATW;
	comMap["ALLUSER"] = COMMAND::ALLUSER;
	comMap["ALLCHATS"] = COMMAND::ALLCHATS;
	comMap["ADDMES"] = COMMAND::ADDMES;
}

Chat::~Chat()
{
	for (int i = 0; i < _User.size(); i++) {
		delete _User[i];
	}
}


Chat::COMMAND Chat::getCommand(std::string& commandFromUser)
{
	std::string cmdFromUSer = parsedPart(commandFromUser);
    return comMap.find(cmdFromUSer)->second;
}

std::string Chat::parsedPart(std::string& stringLine)
{
	std::string parsedPart = stringLine.substr(0,stringLine.find(delim));
	stringLine.erase(0,stringLine.find(delim) + 1);
    return parsedPart;
}

std::string Chat::regis(std::string& commandFromUser)
{
	clear_screen();
	std::string login = parsedPart(commandFromUser);
	std::string name = parsedPart(commandFromUser);
	std::string tmppasw = parsedPart(commandFromUser);
	char pasw[LOGINLENGTH];
	std::fill(pasw, pasw+LOGINLENGTH, '1');
	for(int i = 0; i < tmppasw.size(); i++){
		pasw[i] = tmppasw[i];
	}
	std::string succes = "succes";
	uint* sh1 = sha1(pasw, LOGINLENGTH);
	User* newUser = nullptr;
	if (_User.empty()) {
		newUser = new User(name, login, sh1);
		_User.push_back(newUser);
		//std::cout << "Успешная регистрация!\n";
		return succes;
	}
	else {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() == login) {
				//std::cout << "Логин занят, попробуйте другой!\n";
				std::string notSucces = "Логин занят, попробуйте другой!\n";
				return notSucces;
			}
			else {
				newUser = new User(name, login, sh1);
				_User.push_back(newUser);
				//std::cout << "Успешная регистрация!\n";
				return succes;
			}
		}
	}
	std::string ubAnswer = "что то пошло не так\n";
	return ubAnswer;
}

std::string Chat::auth(std::string& commandFromUser)
{
	clear_screen();
	std::string login = parsedPart(commandFromUser);
	std::string tmppasw = parsedPart(commandFromUser);
	char pasw[LOGINLENGTH];
	std::fill(pasw, pasw+LOGINLENGTH, '1');
	for(int i = 0; i < tmppasw.size(); i++){
		pasw[i] = tmppasw[i];
	}
	uint* sh1 = sha1(pasw, LOGINLENGTH);
	std::string succes = "succes";
	for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			if (_User[i]->checkPass(sh1)) {
				//std::cout << "успешная авторизация!\n";
				return succes;
			}
			else {
				std::string wrongPasw = "неверный пароль!\n";
				return wrongPasw;
			}
		}
	}
	std::string nonExistUser = "Пользователя с данным логином не существует!\n";
	return nonExistUser;
}

std::string Chat::chatw(std::string& commandFromUser)
{
	clear_screen();
	std::string text;
	User* tmpMe = nullptr;
	User* tmpOther = nullptr;
	std::string wayOfChoose = parsedPart(commandFromUser);
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	std::string tmpNumb = parsedPart(commandFromUser);


	if(std::stoi(tmpNumb) > _User.size() - 1)
		return "error input";


	if(wayOfChoose == "userway"){
		tmpOther = this->userChoice(std::stoi(tmpNumb),tmpMe);
	}
	else{
		tmpOther = this->chatChoice(std::stoi(tmpNumb),tmpMe);
	}
	text.clear();
	return text = tmpMe->showOneChat(tmpOther);
}

std::string Chat::addmes(std::string& commandFromUser)
{
    clear_screen();
	
	User* tmpMe = nullptr;
	User* tmpOther = nullptr;
	std::string wayOfChoose = parsedPart(commandFromUser);
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	std::string tmpNumb = parsedPart(commandFromUser);
	if(wayOfChoose == "userway"){
		tmpOther = this->userChoice(std::stoi(tmpNumb),tmpMe);
	}
	else{
		tmpOther = this->chatChoice(std::stoi(tmpNumb),tmpMe);
	}
	std::string text = parsedPart(commandFromUser);
	tmpMe->sendMes(text, tmpMe, tmpOther);
	text.clear();	
	return text = tmpMe->showOneChat(tmpOther);
}

std::string Chat::alluser(std::string& commandFromUser)
{
	std::string temp;
	User* tmpMe = nullptr;
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	temp += std::to_string(_User.size() - 1) + this->delim;
	int counter = 0;
	if (_User.size() > 1) {
		for (int i = 0; i < _User.size(); i++) {
			if (_User[i]->getLog() != tmpMe->getLog()) {
				counter++;
				temp += std::to_string(counter) + " " + _User[i]->getName() + "  |  " + _User[i]->getLog() + "\n";
				//std::cout << counter << " " << _User[i]->getName() << "  |  " << _User[i]->getLog() << "\n\n";
			}
		}
		return temp;
	}
	else
		return temp += "Вы единственный пользователь :-(\n";
}

std::string Chat::allchats(std::string& commandFromUser)
{
	std::string temp;
	User* tmpMe = nullptr;
	std::string tmpLogin = parsedPart(commandFromUser);
	tmpMe = this->findMain(tmpLogin);
	temp.clear();
	temp += std::to_string(tmpMe->getCountOfChats()) + this->delim;
	if (!tmpMe->isEmptyMes()) {
		temp += tmpMe->showAllChats();
		return temp;
	}
	else{
		return temp += "Пока нет диалогов :-(\n";
		//НАДО ПЕРЕДЕЛАТЬ!!!
	}
    // TODO: insert return statement here
}



// void Chat::showUsers(User* user) const
// {
// 	std::string temp;
// 	clear_screen();
// 	int counter = 0;
// 	if (_User.size() > 1) {
// 		temp = "Выберите пользователя или введите 0 для возврата\n";
// 		for (int i = 0; i < _User.size(); i++) {
// 			if (_User[i]->getLog() != user->getLog()) {
// 				counter++;
// 				temp += std::to_string(counter) + " " + _User[i]->getName() + "  |  " + _User[i]->getLog() + "\n";
// 				//std::cout << counter << " " << _User[i]->getName() << "  |  " << _User[i]->getLog() << "\n\n";
// 			}
// 		}
// 		temp.clear();
// 	}
// 	else
// 		temp = "Вы единственный пользователь :-(\n";
// }

// void Chat::showChats(User* user)
// {
// 	std::string temp;
// 	clear_screen();
// 	if (!user->isEmptyMes()) {
// 		temp.clear();
// 		temp = "Введите номер диалога или 0 для возврата\n";
// 		temp += user->showAllChats();
// 		temp.clear();
// 	}
// 	else{
// 		temp = "Пока нет диалогов :-(\nНажмите Enter для возврата\n";
// 		//НАДО ПЕРЕДЕЛАТЬ!!!
// 	}
// }

User *Chat::findMain(std::string login)
{
    for (int i = 0; i < _User.size(); i++) {
		if (_User[i]->getLog() == login) {
			return _User[i];
		}
	}
	return nullptr;
}

User *Chat::chatChoice(int number, User *me)
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

// std::string& Chat::chatting(std::string& commandFromUser)
// {
// 	clear_screen();
// 	User* tmpMe = nullptr;
// 	User* tmpOther = nullptr;
// 	std::string wayOfChoose = parsedPart(commandFromUser);
// 	std::string tmpLogin = parsedPart(commandFromUser);
// 	tmpMe = this->findMain(tmpLogin);
// 	std::string tmpNumb = parsedPart(commandFromUser);
// 	if(wayOfChoose == "userway"){
// 		tmpOther = this->userChoice(std::stoi(tmpNumb),tmpMe);
// 	}
// 	else{
// 		tmpOther = this->chatChoice(std::stoi(tmpNumb),tmpMe);
// 	}
	
// 	std::string text;
// 	bool chattingStatus = true;
// 	while (chattingStatus) {
// 		text.clear();
// 		text = tmpMe->showOneChat(tmpOther);
// 		// _Server->sendTo(text);
// 		// text.clear();
// 		text.clear();
// 		if (text[0] == '0' && text.size() == 1) {
// 			chattingStatus = false;
// 			break;
// 		}
// 		else if (text.size() > 1) {
// 			tmpMe->sendMes(text, tmpMe, tmpOther);
// 		}
// 	}
// }

// int Chat::chatSize() const
// {
// 	return _User.size();
// }


