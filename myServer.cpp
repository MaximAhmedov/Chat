#include "myServer.h"

myServer::myServer(){
    this->startToListen();
};
myServer::~myServer(){
    this->stopServer();
};
void myServer::startToListen(){
    WIN(iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0){
        std::cout << "WSAStartup failed: " << iResult << std::endl;
    }
    else
        std::cout << "WSAStartup is ok" << std::endl;);

    ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(ListenSocket == INVALID_SOCKET){
        std::cout << "Error at socket(): " <<  std::endl;
        WIN(WSACleanup());
    }
    else
        std::cout << "Socket() is ok" << std::endl;

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);

    iResult = bind( ListenSocket,(struct sockaddr*) &serveraddress, sizeof(serveraddress));
    if(iResult == SOCKET_ERROR){
        std::cout << "bind failed with error: " << std::endl;
        WIN(closesocket(ClientSocket))NIX(close(ClientSocket));
        WIN(WSACleanup());
    }
    else
        std::cout << "bind is ok" << std::endl;

    iResult = listen(ListenSocket,5);
    if(iResult==SOCKET_ERROR){
        std::cout << "listen failed: " << std::endl;
        WIN(closesocket(ClientSocket))NIX(close(ClientSocket));
        WIN(WSACleanup());
    }
    else
        std::cout << "listen is ok" << std::endl;
};

void myServer::accepting(){
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if(ClientSocket == INVALID_SOCKET){
        std::cout << "accept failed"  <<std::endl;
        WIN(closesocket(ClientSocket))NIX(close(ClientSocket));
        WIN(WSACleanup());
    }
    else
        std::cout << "accept is ok" << std::endl;
}

std::string myServer::recFrom(){
    bzero(recvBuff, recvBuffLen);
    std::string message;
    message.clear();
    recv(ClientSocket,recvBuff,recvBuffLen,0);
    message = recvBuff;
    std::cout << "Data received from client: " << message << std::endl;
    return message;
};

void myServer::sendTo(std::string& message){
    // bzero(recvBuff, recvBuffLen);
    // message.clear();
    // std::cout << "Enter your message to the client: " << std::endl;
    // std::getline(std::cin, message, '\n');
    send(ClientSocket,message.c_str(),message.length(),0);
};

void myServer::stopServer(){
    shutdown(ClientSocket, 1);
    WIN(closesocket(ClientSocket))NIX(close(ClientSocket));
    WIN(WSACleanup());
};