//
// Created by sigalit on 25.1.2020.
//

#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <vector>

namespace server_side {

    class MyParallelServer : public Server {

    private:
        int m_serverSocket;
        sockaddr_in address;
        bool m_stopFlag;
    public:
        MyParallelServer();
        void runServer(std::vector<ClientHandler*> clientHandlerVec);
        virtual void open(int port, std::vector<ClientHandler*> clientHandlerVec);
        virtual void stop();
        void runClientHandler(int clientSd, ClientHandler *clientHandler);
    };
}

#endif //MILESTONE2_MYPARALLELSERVER_H
