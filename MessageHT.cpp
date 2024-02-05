#include<iostream>
#include "MessageHT.h"

HashTable::HashTable() {
	mem_size = 8;
	mess_tops = new Message * [mem_size];
	for (int i = 0; i < mem_size; i++) {
		mess_tops[i] = nullptr;
	}
	count = 0;
}

HashTable::~HashTable() {
	for (int i = 0; i < mem_size; i++) {
		if (mess_tops[i] != nullptr) {
			delete mess_tops[i];
		}
	}
	delete[] mess_tops;
}

int HashTable::hash_func(const std::string& name) {
	int sum = 0;
	char* login = new char[name.length() + 1];
	strcpy(login, name.c_str());

	for (int i = 0; i < strlen(login); i++) {
		sum += login[i];
	}
	return std::abs(sum) % mem_size;
}

void HashTable::send(std::string& text, const std::string& name) {
	int index = hash_func(name);
	if (mess_tops[index] != nullptr) {
		Message* lastOne = mess_tops[index];
		while (lastOne->next != nullptr) {
			lastOne = lastOne->next;
		}
		Message* newMessage = new Message(text, name);
		lastOne->next = newMessage;
	}
	else {
		mess_tops[index] = new Message(text, name);
	}
	count++;
}

void HashTable::getBy(std::string& text, const std::string& name){
	int index = hash_func(name);
	if (mess_tops[index] != nullptr) {
		Message* lastOne = mess_tops[index];
		while (lastOne->next != nullptr) {
			lastOne = lastOne->next;
		}
		Message* newMessage = new Message(text, name);
		lastOne->next = newMessage;
		newMessage->sended = false;
	}
	else {
		mess_tops[index] = new Message(text, name);
		mess_tops[index]->sended = false;
	}
	
	count++;
}

void HashTable::showMessages(const std::string& name)
{
	int index = hash_func(name);
	Message* start = mess_tops[index];
	if (start == nullptr)
		std::cout << "Напишите первое сообщение!\n";
	else {
		do {
			if (start->sended == true) {
				std::cout << std::string(3,'\t');
			}
			std::cout << start->_text << '\n';
			start = start->next;
		} while (start != nullptr);
	}
}

void HashTable::showMessWithAll() const
{
	int counter = 0;
		for (int i = 0; i < mem_size; i++) {
			if (mess_tops[i] != nullptr) {
				Message* last = mess_tops[i];
				while (last->next != nullptr) {
					last = last->next;
				}
				counter++;
				std::cout << counter << " " << last->_name << "\n\t" << last->_text << '\n';
			}
		}
}

std::string& HashTable::getNameHT(int number) const
{
	int counter = 0;
	for (int i = 0; i < mem_size; i++) {
		if (mess_tops[i] != nullptr) {
			counter++;
			if (counter == number) {
				return mess_tops[i]->_name;
			}
		}
	}
}

bool HashTable::isEmpty()
{
	for (int i = 0; i < mem_size; i++) {
		if (mess_tops[i] != nullptr) {
			return false;
		}
	}
	return true;
}
