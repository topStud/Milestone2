
#include "MySerialServer.h"
using namespace server_side;
MySerialServer::MySerialServer()
{
    m_stopFlag= false;
}

void MySerialServer::open(int port,std::vector<ClientHandler*> clientHandlerVec)
{
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket == -1)
    {
        //error
        throw "Could not create a socket";
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    //the actual bind command
    if (bind(m_serverSocket, (struct sockaddr *) &address, sizeof(address)) == -1)
    {
        throw "Could not bind the socket to an IP";
    }

    std::thread server_thread(&MySerialServer::runServer,this,clientHandlerVec[0]);
    server_thread.detach();
}

void MySerialServer::runServer(ClientHandler *clientHandler)
{
    while(!m_stopFlag)
    {
        if (listen(m_serverSocket, 1) == -1) {
            throw "Error during listening command";
        } else{
            std::cout<<"Server is now listening ..."<<std::endl;
        }

        //Set timout of 2 minutes for server socket listening to client
        struct timeval tv{};
        tv.tv_sec = 120;
        tv.tv_usec = 0;
        int s = setsockopt(m_serverSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

        // accepting a client
        int clientSocket = accept(m_serverSocket, (struct sockaddr *)&address,
                                (socklen_t*)&address);

        if (clientSocket == -1) {
            std::cout << "No client accepted"<< std::endl;
            stop();
        } else {
            std::cout << "Client accepted" << std::endl;
            clientHandler->handle_client(clientSocket);
            close(clientSocket);
        }
    }
    std::cout << "Closing the listening socket"<<std::endl;
    close(m_serverSocket);
}

void MySerialServer::stop()
{
    m_stopFlag = true;
}