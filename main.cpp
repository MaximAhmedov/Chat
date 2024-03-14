#include <iostream>
#include <algorithm>
#include "Chat.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() clear
#endif

int main() {
	
	Chat chat;
	User* me = nullptr;
	User* other = nullptr;
	bool chatCon = true;

	while (chatCon) {
		clear_screen();
		std::string name;
		std::string login;
		char pass[LOGINLENGTH];
		std::fill(pass, pass+LOGINLENGTH, '1');
		int choice;
		std::cout << "\t1 - Войти\n \t2 - Регистрация\n \t3 - Выход\n";
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
					if (!chat.authData(login, pass))
						break;
					me = chat.auth(login,pass,LOGINLENGTH);
					if (me) { authCon = false; }
				}
				break; }
			case 2:
			{
				bool regCon = true;
				while (regCon) {
					if (!chat.regData(name, login, pass, LOGINLENGTH))
						break;
					me = chat.regis(name,login,pass,LOGINLENGTH);
					if (me) { regCon = false; }
				}
				break; 
			}
			default:
				std::cout << "Ошибка!\n";
				break;
		}

		if (me) {
			bool inChatCon = true;
			while (inChatCon) {
				int inChat;
				std::cout << "\t1 - Все пользователи\n \t2 - Мои Сообщения\n \t3 - Выход из аккаунта\n";
				std::cin >> inChat;

				switch (inChat) {
				case 1:
				{
					chat.showUsers(me);
					if (chat.chatSize() > 1) {
						std::cout << "Выберите пользователя или введите 0 для возврата\n";
						int friendChoice;
						std::cin >> friendChoice;
						other = chat.userChoice(friendChoice, me);
						if (other) {
							
							chat.chatting(me, other);
						}
					}
					other = nullptr;
					break;
				}
				case 2:
				{
					chat.showChats(me);
					if (!me->isEmptyMes()) {
						int friendChoice;
						std::cin >> friendChoice;
						other = chat.chatChoice(friendChoice, me);
						if (other) {
							
							chat.chatting(me, other);
						}
						other = nullptr;
					}
					break;
				}
				case 3:
				{
					inChatCon = false;
					break;
				}
				default:
					std::cout << "Ошибка!\n";
					break;
				}
			}
		}
		if (me)
			me = nullptr;
		if (other)
			other = nullptr;
	}
	return 0;
}