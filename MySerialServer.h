
#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
using namespace server_side;

class MySerialServer: public Server {

private:
    int m_serverSocket;
    sockaddr_in address;
    bool m_stopFlag;
    /*
    int m_clientSocket;
    std::string m_tempString;*/
public:
    MySerialServer();
    void runServer(ClientHandler *clientHandler);
   // bool getStopFlag() {return m_stopFlag;}
    //int getserverSocket() {return m_serverSocket;}
    virtual void open(int port,ClientHandler &clientHandler);
    virtual void stop();
  //dtor

  /*public:
    Server(int port);
    void createSocket();
    int get_clientSocket();
    void bindSocket();
    void listenAndAccept();
    void readDataFromClient();*/
};


// global
//void runServer(MySerialServer &server,ClientHandler &clientHandler);

#endif //MILESTONE2_MYSERIALSERVER_H
