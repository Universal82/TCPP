#include <netinet/in.h>

namespace MissMoss{
    namespace TCP{
        class Client{
            public:
                Client(std::string addressToConnectTo, int portToConnectOn, std::function<char *(char *)> dataHandler);
                Client(char *addressToConnectTo, int portToConnectOn, std::function<char *(char *)> dataHandler);
                void sendData(char *dataToSend);
                void sendData(std::string dataToSend);
                void operator<<(char *dataToSend);
                void operator<<(std::string dataToSend);
                char *awaitPacket();
                void operator>>(char *dataToSend);
                void operator>>(std::string *dataToSend);
                sockaddr_in Address;
                int _Client;
                int status;
                char *messageBuff;
        };

        class Server{
            public:
                Server();
                void startListener(int portToListenOn,std::function<char *(char *)> dataHandler);
                sockaddr_in Address;
                char *messageBuff;
        };
    }
}