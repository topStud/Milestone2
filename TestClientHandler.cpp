//
// Created by topaz on 12/01/2020.
//

#include "TestClientHandler.h"
bool TestClientHandler::stop_flag = false;

void TestClientHandler::handle_client(int client_sd) {
  std::string problem{};
  std::string solution{};
  while (true) {
    // checks if the communication stopped
    if (TestClientHandler::stop_flag) {
      break;
    }

   /* getline(input_stream, problem);
    if (cache_manager_->exist_in_cache(problem)){
      output_stream << cache_manager_->get(problem);
    } else {
      solution = solver_->solve(problem);
      cache_manager_->save(problem, solution);
      output_stream << solution;
    }*/
  }
}


