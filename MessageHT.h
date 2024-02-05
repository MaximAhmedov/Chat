#pragma once
#include <iostream>

class HashTable {
public:

    HashTable();
    ~HashTable();

    void send(std::string& text, const std::string& name);
    void getBy(std::string& text, const std::string& name);
    void showMessages(const std::string& name);
    void showMessWithAll()const;
    std::string& getNameHT(int number) const;
    bool isEmpty();

private:
    class Message {
    public:
        std::string _text;
        std::string _name;
        Message* next;
        bool sended;
    
        Message(std::string& text,const std::string& name) : _text(text), _name(name) {
            next = nullptr;
            sended = true;
        }
        ~Message() {
            if (next != nullptr)
                delete next;
        }
    };
    int hash_func(const std::string& name);

    Message** mess_tops;
    int mem_size;
    int count;


};

