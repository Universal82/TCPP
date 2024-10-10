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
        Client::Client(std::string addressToConnectTo, int portToConnectOn, std::function<char *(char *)> dataHandler){
            //begin init with addressToConnectTo as a std::string
            //set all address bytes to 0
            bzero((char*)&this->Address, sizeof(this->Address));
            //get host IP using it's hostname (if it's not already an IP)
            struct hostent* host = gethostbyname((char *)addressToConnectTo.c_str());
            //set IP type to IPV4
            this->Address.sin_family = AF_INET;
            //set the address to connect to
            this->Address.sin_port = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
            //set the port to listen on
            this->Address.sin_port = htons(portToConnectOn);
            //initilize client socket as TCP
            this->_Client = socket(AF_INET,SOCK_STREAM,0);
            //attempt to connect and set status
            this->status = connect(this->_Client, (sockaddr*) &this->Address, sizeof(this->Address));
            //if an error is thrown close the program (will change this later to actually throw an error)
            if(this->status < 0){ printf("Error connecting to socket!\n"); exit(-1); }
            //if connected sucessfully state that in the terminal
            printf("Connected to the server!\n");
            //init finished
        }

        Client::Client(char *addressToConnectTo, int portToConnectOn, std::function<char *(char *)> dataHandler){
            //begin init with addressToConnectTo as a char *
            //set all address bytes to 0
            bzero((char*)&this->Address, sizeof(this->Address));
            //get host IP using it's hostname (if it's not already an IP)
            struct hostent* host = gethostbyname(addressToConnectTo);
            //set IP type to IPV4
            this->Address.sin_family = AF_INET;
            //set the address to connect to
            this->Address.sin_port = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
            //set the port to listen on
            this->Address.sin_port = htons(portToConnectOn);
            //initilize client socket as TCP
            this->_Client = socket(AF_INET,SOCK_STREAM,0);
            //attempt to connect and set status
            this->status = connect(this->_Client, (sockaddr*) &this->Address, sizeof(this->Address));
            //if an error is thrown close the program (will change this later to actually throw an error)
            if(this->status < 0){ printf("Error connecting to socket!\n"); exit(-1); }
            //if connected sucessfully state that in the terminal
            printf("Connected to the server!\n");
            //init finished
        }
        
        //I'm 12% sure I'll need this later for some reason
        /*while (messageBuff != "exit"){
                //char *ReplyBuff = std::invoke(packetRecievedHandler, messageBuff);
                std::this_thread::sleep_for(0.1s);
                this->sendData(dataHandler(messageBuff));
                std::cout << "Awaiting server response..." << std::endl;
                recv(this->_Client, (char*)&this->messageBuff, sizeof(this->messageBuff), 0);
            }
        }*/

        void Client::sendData(char *dataToSend){
            send(this->_Client, (char*)&dataToSend, strlen(dataToSend), 0);
        }

        void Client::sendData(std::string dataToSend){
            send(this->_Client, (char*)&dataToSend, strlen((char *)dataToSend.c_str()), 0);
        }

        void Client::operator<<(char *dataToSend){
            this->sendData(dataToSend);
        }

        void Client::operator<<(std::string dataToSend){
            this->sendData(dataToSend);
        }

        char *Client::awaitPacket(){
            recv(this->_Client,this->messageBuff,sizeof(this->messageBuff),0);
            return messageBuff;
        }

        /*std::string Client::awaitPacket()
        {
            recv(this->_Client,this->messageBuff,sizeof(this->messageBuff),0);
            return messageBuff;
        }*/

        void Client::operator>>(char *bufferToSaveTo){
            bufferToSaveTo = this->awaitPacket();
        }

        void Client::operator>>(std::string *bufferToSaveTo){
            *bufferToSaveTo = this->awaitPacket();
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

