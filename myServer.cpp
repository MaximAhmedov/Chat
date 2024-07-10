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
}
void myServer::fdStart() {
    FD_ZERO(&(this->master));
    FD_SET(this->ListenSocket,&(this->master));
}
int myServer::selectFunc()
{
    this->copy = this->master;    
    return select(0, &(this->copy), nullptr, nullptr, nullptr);;
}
void myServer::mainFunc(int i) {

    std::string response;

    selectSock = copy.fd_array[i];
    if(selectSock == ListenSocket){
        selectClSocket = accept(ListenSocket,nullptr,nullptr);
        FD_SET(selectClSocket,&master);
    }
    else{      
        bzero(recvBuff, recvBuffLen);
        int bytesIn = recv(selectSock,recvBuff,recvBuffLen,0);
        if(bytesIn <= 0){
            WIN(closesocket(selectSock))NIX(close(selectSock));
            FD_CLR(selectSock,&master);
        }
        else{
            //message->clear();
            response.clear();
            std::string message = recvBuff;
            std::cout << "Data received from client: " << message << std::endl;
            switch(chat.getCommand(message)){
                case chat.REGIS:{
                    response = chat.regis(message);
                    send(selectSock,response.c_str(),response.length(),0);
                    break;
                }
                case chat.SIGNIN:{
                    response = chat.auth(message);
                    send(selectSock,response.c_str(),response.length(),0);
                    break;
                }
                case chat.CHATW:{
                    response = chat.chatw(message);
                    send(selectSock,response.c_str(),response.length(),0);
                    break;
                }
                case chat.ADDMES:{
                    response = chat.addmes(message);
                    send(selectSock,response.c_str(),response.length(),0);
                    break;
                }
                case chat.ALLUSER:{
                    response = chat.alluser(message);
                    send(selectSock,response.c_str(),response.length(),0);
                    break;
                }
                case chat.ALLCHATS:{
                    response = chat.allchats(message);
                    send(selectSock,response.c_str(),response.length(),0);
                    break;
                }
                default:
                    break;
            }
            // bzero(recvBuff, recvBuffLen);
            // message.clear();
            // std::cout << "Enter your message to the client: " << std::endl;
            // std::getline(std::cin, message, '\n');
            // send(selectSock,message.c_str(),message.length(),0);

        }
    }
};

void myServer::stopServer(){
    shutdown(ClientSocket, 1);
    WIN(closesocket(ClientSocket))NIX(close(ClientSocket));
    WIN(WSACleanup());
};
// std::string myServer::recFrom(){
//     bzero(recvBuff, recvBuffLen);
//     std::string message;
//     message.clear();
//     recv(ClientSocket,recvBuff,recvBuffLen,0);
//     message = recvBuff;
//     std::cout << "Data received from client: " << message << std::endl;
//     return message;
// };

// void myServer::sendTo(std::string& message){
//     // bzero(recvBuff, recvBuffLen);
//     // message.clear();
//     // std::cout << "Enter your message to the client: " << std::endl;
//     // std::getline(std::cin, message, '\n');
//     send(ClientSocket,message.c_str(),message.length(),0);
// };

