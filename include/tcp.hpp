#include <netinet/in.h>

namespace MissMoss{
    namespace TCP{
        class Client{
            public:
                Client();
                void connectTo(char *addressToConnectTo, int portToConnectOn, std::function<char *(char *)> dataHandler);
                void sendData(char *dataToSend);
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