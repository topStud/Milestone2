//
// Created by topaz on 12/01/2020.
//

#ifndef MILESTONE2__TESTCLIENTHANDLER_H_
#define MILESTONE2__TESTCLIENTHANDLER_H_

#include <unistd.h>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class TestClientHandler : public ClientHandler {
  Solver<std::string, std::string>* solver_;
  CacheManager<std::string>* cache_manager_;
 public:
  TestClientHandler(Solver<std::string, std::string>* solver, CacheManager<std::string>* cache) : solver_(solver), cache_manager_(cache) {}
  static bool stop_flag;
  void handle_client(int client_sd) override;
};

#endif //MILESTONE2__TESTCLIENTHANDLER_H_
