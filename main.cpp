#include <iostream>
#include <thread>
#include <string.h>
#include <functional>

#include "include/tcp.hpp"

char *handler(char *dataToHandle){
    int i = 0;
    if (i<10){
        return (char *)(std::string("Recieved: ") + dataToHandle + "!").c_str();
    } else {
        return (char *)"exit";
    }
}

void makeClient(){
    MissMoss::TCP::Client ClientVal;
    ClientVal.connectTo((char *)"127.0.0.1",2000,(std::function<char *(char *)>)handler);
}

void makeServer(){
    MissMoss::TCP::Server ServerVal;
    ServerVal.startListener(20000,(std::function<char *(char*)>)handler);
}

int main(){
    //std::thread ServerThread(&makeServer);
    std::thread ClientThread(&makeClient);
}