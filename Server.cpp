//
// Created by sigalit on 26.1.2020.
//

#include "Server.h"
#define DEFAULT_TIMEOUT 12;

using namespace server_side;

/**
 * stop function.
 * sets the value of the flag to true.
 * it happens when we want to terminate the main loop.
 */
void ServerAbs::stop()
{
    m_stopFlag = true;
}

/**
 * create_and_bind function- creates a socket and binds it to the port.
 * @param port - port number
 */
void ServerAbs::create_and_bind(int port)
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
}

/**
 * set_socket_timeout function.
 * sets timeout for the sever socket
 */
void ServerAbs::set_socket_timeout()
{
    struct timeval tv{};
    tv.tv_sec = DEFAULT_TIMEOUT;
    tv.tv_usec = 0;
    int s = setsockopt(m_serverSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
}