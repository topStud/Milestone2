
#include "MySerialServer.h"

MySerialServer::MySerialServer()
{
    m_stopFlag= false;
}

void MySerialServer::open(int port,ClientHandler &clientHandler)
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

    std::thread server_thread(&MySerialServer::runServer,this,&clientHandler);
    server_thread.detach();
}

void MySerialServer::runServer(ClientHandler *clientHandler)
{
    while(m_stopFlag==false)
    {
        if (listen(m_serverSocket, 1) == -1) {
            throw "Error during listening command";
        } else{
            std::cout<<"Server is now listening ..."<<std::endl;
        }

        //Set timout of 2 minutes for server socket listening to client
        struct timeval tv;
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
/*
void Server::listenAndAccept()
{
    if (listen(m_serverSocket, 1) == -1) {
        throw "Error during listening command";
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    m_clientSocket = accept(m_serverSocket, (struct sockaddr *)&address,
                            (socklen_t*)&address);

    if (m_clientSocket == -1) {
        throw "Error accepting client";
    } else {
        std::cout << "accepted the client" << std::endl;
    }

    //closing the listening socket
    close(m_serverSocket);
}

void Server::readDataFromClient()
{
    char buffer[1025] = {0};
    buffer[1024] = '\0';

    int val_read = read( m_clientSocket , buffer, 1024);
    if (val_read == -1) {
        std::cout << "Error reading the data from the simulator" << std::endl;
    }
    std::string str(buffer);
    std::string::size_type pos = 0;
    while ((pos = str.find('\n', 0)) != std::string::npos)
    {
        this->m_tempString.append(str.substr(0, pos));
        std::vector<double> vec = splitString();
        for(unsigned int i=0; i< this->m_commandsVec.size(); i++)
        {
            if (SymbolTable::get_instance()->is_key_exists_in_sim_map(this->m_commandsVec[i]))
            {
                SymbolTable::get_instance()->get_value_from_sim_map(this->m_commandsVec[i])->set_value(vec[i]);
            }
        }
        str= str.substr(pos+1);
        this->m_tempString.clear();
    }
    this->m_tempString.append(str);
}

int Server::get_clientSocket() {
    return this->m_clientSocket;
}

std::vector<double> Server::splitString() const
{
    std::vector<double> vec;
    std::stringstream ss(this->m_tempString);

    for (double i; ss >> i;)
    {
        vec.push_back(i);
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
    }
    return vec;
}

void runServer(Server server)
{
    utilities::server_mutex.lock();
    while(true)
    {
        if (utilities::flag_stop_communication) {
            close(server.get_clientSocket());
            break;
        }
        server.readDataFromClient();
    }
    utilities::server_mutex.unlock();
}
*/