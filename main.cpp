#include <iostream>
#include "Chat.h"
#include <windows.h>


int main() {
	
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Chat chat;
	User* me = nullptr;
	User* other = nullptr;
	std::string name;
	std::string login;
	std::string pasw;
	bool chatCon = true;

	while (chatCon) {
		system("cls");
		int choice;
		std::cout << "\t1 - Войти\n \t2 - Зарегестрироваться\n \t3 - Выйти из программы\n";
		std::cin >> choice;

		if (choice == 3) {
			chatCon = false;
			break;
		}

		switch (choice)
		{
			case 1:
			{
				bool authCon = true;
				while (authCon) {
					std::cout << "Введите логин\n";
					std::cin >> login;
					std::cout << "Введите пароль\n";
					std::cin >> pasw;
					me = chat.auth(login, pasw);
					if (me) { authCon = false; }
				}
				break; }
			case 2:
			{
				bool regCon = true;
				std::string pasw2;
				while (regCon) {
					std::cout << "Введите имя\n";
					std::cin >> name;
					std::cout << "Введите логин\n";
					std::cin >> login;
					std::cout << "Введите пароль\n";
					std::cin >> pasw;
					std::cout << "Повторите пароль\n";
					std::cin >> pasw2;
					if (pasw == pasw2) {
						me = chat.regis(name, login, pasw);
					}
					else
						std::cout << "пароли не совпадают!\n";
					if (me) { regCon = false; }
				}
				break; 
			}
			default:
				std::cout << "Неверный ввод!\n";
				break;
		}

		if (me) {

			bool inChatCon = true;
			while (inChatCon) {
				int inChat;
				std::cout << "\t1 - все пользователи\n \t2 - мои друзья\n \t3 - мои сообщения\n \t4 - выйти из аккаунта\n";
				std::cin >> inChat;

				switch (inChat) {
				case 1:
				{
					chat.showUsers(me);
					if (chat.chatSize() > 1) {
						std::cout << "Выберите пользователя, что написать ему сообщение или 0 чтобы вернутся на предыдущий экран\n";
						int friendChoice;
						std::cin >> friendChoice;
						other = chat.userChoice(friendChoice, me);
						if (other) {
							me->showOneChat(other);
							chat.chatting(me, other);
						}
					}
					other = nullptr;
					break;
				}
				case 2:
				{
					system("cls");
					std::cout << "Эта функция пока недоступна :-(\n";
					break;
				}
				case 3:
				{
					chat.showChats(me);
					if (!me->isEmptyMes()) {
						int friendChoice;
						std::cin >> friendChoice;
						other = chat.chatChoice(friendChoice, me);
						if (other) {
							me->showOneChat(other);
							chat.chatting(me, other);
						}
						other = nullptr;
					}
					break;
				}
				case 4:
				{
					inChatCon = false;
					break;
				}
				default:
					std::cout << "Неверный ввод!\n";
					break;
				}
			}
			User* me = nullptr;
			User* other = nullptr;
		}
		
	}
	return 0;
}