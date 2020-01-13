//
// Created by topaz on 12/01/2020.
//

#ifndef MILESTONE2__CLIENTHANDLER_H_
#define MILESTONE2__CLIENTHANDLER_H_
#include <iostream>
class ClientHandler {
 public:
  virtual void handle_client(std::istream input_stream, std::ostream output_stream) = 0;
};

#endif //MILESTONE2__CLIENTHANDLER_H_
