
#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H
#include "ServerAbs.h"
#include <thread>
#include <vector>

namespace server_side {

    class MySerialServer : public ServerAbs {

    public:
        void runServer(ClientHandler *clientHandler);
        virtual void open(int port, std::vector<ClientHandler*> clientHandlerVec);
    };
}


#endif //MILESTONE2_MYSERIALSERVER_H
