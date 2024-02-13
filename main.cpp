#include <iostream>
#include <algorithm>
#include "Chat.h"
#include <windows.h>


int main() {
	
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Chat chat;
	User* me = nullptr;
	User* other = nullptr;
	bool chatCon = true;

	while (chatCon) {
		system("cls");
		std::string name;
		std::string login;
		char pass[LOGINLENGTH];
		std::fill(pass, pass+LOGINLENGTH, '1');
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
				std::cout << "Неверный ввод!\n";
				break;
		}

		if (me) {
			bool inChatCon = true;
			while (inChatCon) {
				int inChat;
				std::cout << "\t1 - все пользователи\n \t2 - мои сообщения\n \t3 - выйти из аккаунта\n";
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
					std::cout << "Неверный ввод!\n";
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