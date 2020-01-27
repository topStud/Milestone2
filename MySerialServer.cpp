
#include "MySerialServer.h"
using namespace server_side;

/**
 * open function- creates a socket and binds it to the port.
 * @param port - port number
 * @param clientHandlerVec - vector containing many(10) client handlers
 */
void MySerialServer::open(int port,std::vector<ClientHandler*> clientHandlerVec)
{
    create_and_bind(port);
    std::thread server_thread(&MySerialServer::runServer,this,clientHandlerVec[0]);
    server_thread.detach();
}

/**
 * runServer function - waits for clients and accepts them.
 * creates a separate thread for each client.
 * @param clientHandlerVec - vector containing many(10) client handlers
 */
void MySerialServer::runServer(ClientHandler *clientHandler)
{
    server_mutex.lock();
    while(!m_stopFlag)
    {
        if (listen(m_serverSocket, 1) == -1) {
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
            clientHandler->handle_client(clientSocket);
            close(clientSocket);
        }
    }
    std::cout << "Closing the listening socket"<<std::endl;
    close(m_serverSocket);
    server_mutex.unlock();
}