#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "ClientHandler.h"
#include <vector>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace server_side
{
    /**
    * Server interface.
    */
    class Server
    {
        public:
        virtual void open(int port,std::vector<ClientHandler*> clientHandlerVec)= 0;
        virtual void stop()= 0;
        virtual ~Server()= default;
    };

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

    extern std::mutex server_mutex;
}

#endif //MILESTONE2_SERVER_H
