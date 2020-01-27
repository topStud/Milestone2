//
// Created by sigalit on 25.1.2020.
//

#include "MyParallelServer.h"
using namespace server_side;


/**
 * open function- creates a socket and binds it to the port.
 * @param port - port number
 * @param clientHandlerVec - vector containing many(10) client handlers
 */
void MyParallelServer::open(int port,std::vector<ClientHandler*> clientHandlerVec)
{
    create_and_bind(port);
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
    server_mutex.lock();
    std::vector<std::thread> threads;
    while(!m_stopFlag)
    {
        if (listen(m_serverSocket, 10) == -1) {
            throw "Error during listening command";
        } else{
            std::cout<<"Server is now listening ..."<<std::endl;
        }

        set_socket_timeout();
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
    server_mutex.unlock();
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
