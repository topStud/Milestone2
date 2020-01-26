//
// Created by topaz on 12/01/2020.
//

#ifndef MILESTONE2__CLIENTHANDLER_H_
#define MILESTONE2__CLIENTHANDLER_H_
#include <iostream>
class ClientHandler {
 public:
  virtual void handle_client(int client_sockfd) = 0;
  virtual ~ClientHandler() = default;
};

#endif //MILESTONE2__CLIENTHANDLER_H_
