//
// Created by sigalit on 25.1.2020.
//

#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H

#include "ServerAbs.h"
#include <thread>
#include <vector>

namespace server_side {

    class MyParallelServer : public ServerAbs {

    public:
        void runServer(std::vector<ClientHandler*> clientHandlerVec);
        virtual void open(int port, std::vector<ClientHandler*> clientHandlerVec);
        void runClientHandler(int clientSd, ClientHandler *clientHandler);
    };
}

#endif //MILESTONE2_MYPARALLELSERVER_H
