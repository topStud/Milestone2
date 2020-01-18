//
// Created by topaz on 14/01/2020.
//

#ifndef MILESTONE2__MYCLIENTHANDLER_H_
#define MILESTONE2__MYCLIENTHANDLER_H_

#include <string>
#include <cstring>
#include <unistd.h>

#include "MatrixProblem.h"
#include "MatrixSolverOA.h"
#include "ClientHandler.h"
#include "CacheManager.h"

class MyClientHandler : public ClientHandler{
  Solver<std::string, std::string>* solver_;
  CacheManager<std::string>* cache_manager_;
 public:
  MyClientHandler(Solver<std::string, std::string>* solver, CacheManager<std::string>* cache) : solver_(solver), cache_manager_(cache) {}
  void handle_client(/*std::istream input*/ int client_socket, std::ostream output) override;
};

#endif //MILESTONE2__MYCLIENTHANDLER_H_
