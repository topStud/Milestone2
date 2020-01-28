//
// Created by sigalit on 26.1.2020.
//

#ifndef MILESTONE2_SERVERABS_H
#define MILESTONE2_SERVERABS_H

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define DEFAULT_TIMEOUT 120;

namespace server_side
{
    class ServerAbs : public server_side::Server{

    protected:
        int m_serverSocket;
        sockaddr_in address;
        bool m_stopFlag;
        void create_and_bind(int port);
        void set_socket_timeout();
        ServerAbs():m_stopFlag(false){}


    public:
        virtual void stop();
    };
}

#endif //MILESTONE2_SERVERABS_H
