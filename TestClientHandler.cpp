//
// Created by topaz on 12/01/2020.
//

#include "TestClientHandler.h"
bool TestClientHandler::stop_flag = false;

void TestClientHandler::handle_client(int client_sd) {
  char buffer[1024];
  std::string problem{}, solution{};
  int val_read, val_write;
  while (true) {
    // checks if the communication stopped
    if (TestClientHandler::stop_flag) {
      break;
    }

    val_read = read(client_sd, buffer, 1024);
    if (val_read == -1) {
      std::cerr << "Error reading from client" << std::endl;
    }
    if (cache_manager_->exist_in_cache(buffer)){
      val_write = write(client_sd, cache_manager_->get(buffer).c_str(), cache_manager_->get(buffer).size());
      if (val_write == -1) {
        std::cerr << "Error writing to client" << std::endl;
      }
    } else {
      problem = buffer;
      solution = solver_->solve(&problem);
      cache_manager_->save(problem, solution);
      val_write = write(client_sd, solution.c_str(), solution.size());
      if (val_write == -1) {
        std::cerr << "Error writing to client" << std::endl;
      }
    }
  }
}


