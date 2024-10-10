#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <thread>
#include <functional>
#include <bits/std_function.h>
#include <chrono>

#include "../include/tcp.hpp"

typedef std::function<char *(char *)> handlerFunction;

using namespace std::chrono;
using namespace std::chrono_literals;

namespace MissMoss{
    namespace TCP{
        Client::Client(){}
        
        void Client::connectTo(char *addressToConnectTo, int portToConnectOn, std::function<char *(char *)> dataHandler){
            bzero((char*)&this->Address, sizeof(this->Address)); 
            struct hostent* host = gethostbyname(addressToConnectTo);
            this->Address.sin_family = AF_INET;
            this->Address.sin_port = 
                inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
            this->Address.sin_port = htons(portToConnectOn);
            this->_Client = socket(AF_INET,SOCK_STREAM,0);
            this->status = connect(this->_Client, (sockaddr*) &this->Address, sizeof(this->Address));
            if(this->status < 0){
                std::cout<<"Error connecting to socket!"<<std::endl;
                exit(-1);
            }
            std::cout << "Connected to the server!" << std::endl;
            while (messageBuff != "exit"){
                //char *ReplyBuff = std::invoke(packetRecievedHandler, messageBuff);
                std::this_thread::sleep_for(0.1s);
                this->sendData(dataHandler(messageBuff));
                std::cout << "Awaiting server response..." << std::endl;
                recv(this->_Client, (char*)&this->messageBuff, sizeof(this->messageBuff), 0);
            }
        }

        void Client::sendData(char *dataToSend){
            send(this->_Client, (char*)&dataToSend, strlen(dataToSend), 0);
        }

        Server::Server(){
            this->messageBuff[1500];
            bzero((char*)&this->Address, sizeof(this->Address));
            this->Address.sin_family = AF_INET;
            this->Address.sin_addr.s_addr = htonl(INADDR_ANY);
        }

        void Server::startListener(int portToListenOn, std::function<char *(char *)> dataHandler){
            
        }
    }
}

