
#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <vector>

namespace server_side {

    class MySerialServer : public Server {

    private:
        int m_serverSocket;
        sockaddr_in address;
        bool m_stopFlag;
    public:
        MySerialServer();

        void runServer(ClientHandler *clientHandler);
        virtual void open(int port, std::vector<ClientHandler*> clientHandlerVec);
        virtual void stop();
    };
}

#endif //MILESTONE2_MYSERIALSERVER_H
