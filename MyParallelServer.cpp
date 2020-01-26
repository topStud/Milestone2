//
// Created by sigalit on 25.1.2020.
//

#include "MyParallelServer.h"
using namespace server_side;

/**
 *  constructor.
 *  initializes the flag.
 */
MyParallelServer::MyParallelServer()
{
    m_stopFlag= false;
}

/**
 * open function- creates a socket and binds it to the port.
 * @param port - port number
 * @param clientHandlerVec - vector containing many(10) client handlers
 */
void MyParallelServer::open(int port,std::vector<ClientHandler*> clientHandlerVec)
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

    std::thread server_thread(&MyParallelServer::runServer,this,clientHandlerVec);
    server_thread.detach();
}

/**
 * runServer function - waits for clients and accepts them.
 * creates a separate thread for each client.
 * @param clientHandlerVec - vector containing many(10) client handlers
 */
void MyParallelServer::runServer(std::vector<ClientHandler*> clientHandlerVec)
{
    std::vector<std::thread> threads;
    while(!m_stopFlag)
    {
        if (listen(m_serverSocket, 10) == -1) {
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
            threads.push_back(std::thread(&MyParallelServer::runClientHandler,this, clientSocket,clientHandlerVec[0]));
        }
    }
    std::cout << "Closing the listening socket"<<std::endl;
    close(m_serverSocket);
    for (auto&& t : threads) {
        t.join();
    }
}

/**
 * runClientHandler function - calls a function that handles the client
 * @param clientSd - client socket.
 * @param clientHandler - the client handler object that will handle this specific client.
 */
void MyParallelServer::runClientHandler(int clientSd, ClientHandler* clientHandler)
{
    clientHandler->handle_client(clientSd);
    close(clientSd);
}

/**
 * stop function.
 * sets the value of the flag to true.
 * it happens when we want to terminate the main loop.
 */
void MyParallelServer::stop()
{
    m_stopFlag = true;
}