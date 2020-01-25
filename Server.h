#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "ClientHandler.h"
#include <vector>
namespace server_side
{
    class Server
    {
        public:
        virtual void open(int port,std::vector<ClientHandler*> clientHandlerVec)= 0;
        virtual void stop()= 0;
        virtual ~Server()= default;
    };
}

#endif //MILESTONE2_SERVER_H
