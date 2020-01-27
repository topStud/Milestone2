#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "ClientHandler.h"
#include <vector>
#include <mutex>

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

    extern std::mutex server_mutex;
}

#endif //MILESTONE2_SERVER_H
