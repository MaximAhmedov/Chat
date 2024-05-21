#include <iostream>
#include <algorithm>
#include "Chat.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

int main() {
	
	Chat chat;
	User* me = nullptr;
	User* other = nullptr;
	

	while(true){
	chat.acceptClient();
	bool chatCon = true;
	while (chatCon) {
		std::string name;
		std::string login;
		char pass[LOGINLENGTH];
		std::fill(pass, pass+LOGINLENGTH, '1');
		int choice;
		std::string output;
		std::string input;
		output = "\t1 - Войти\n \t2 - Регистрация\n \t3 - Выход\n";
		chat.responseToClient(output);
		output.clear();
		input = chat.commandFromClient();
		choice = std::stoi(input);
		input.clear();

		if (choice == 3) {
			output = "end connection";
			chat.responseToClient(output);
			output.clear();
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
				output = "Ошибка!\n";
				chat.responseToClient(output);
				output.clear();
				break;
		}

		if (me) {
			bool inChatCon = true;
			while (inChatCon) {
				int inChat;
				output = "\t1 - Все пользователи\n \t2 - Мои Сообщения\n \t3 - Выход из аккаунта\n";
				chat.responseToClient(output);
				output.clear();
				input = chat.commandFromClient();
				inChat = std::stoi(input);
				input.clear();

				switch (inChat) {
				case 1:
				{
					chat.showUsers(me);
					if (chat.chatSize() > 1) {
						// output = "Выберите пользователя или введите 0 для возврата\n";
						// chat.responseToClient(output);
						// output.clear();
						input = chat.commandFromClient();
						int friendChoice = std::stoi(input);
						input.clear();
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
						input = chat.commandFromClient();
						int friendChoice = std::stoi(input);
						input.clear();
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
					output = "Ошибка!\n";
					chat.responseToClient(output);
					output.clear();
					break;
				}
			}
		}
		if (me)
			me = nullptr;
		if (other)
			other = nullptr;
	}
	}
	return 0;
}