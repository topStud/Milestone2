//
// Created by topaz on 14/01/2020.
//

#include <sys/socket.h>
#include "MyClientHandler.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "MatrixHashTable.h"

void MyClientHandler::handle_client(int client_socket) {
    char buffer[1024] = "";
    std::string matrix{}, temp{}, solution{}, sub_str{}, matrix_name{};
    bool stop_loop = false;
    int index;
    do {
        int val_read = read(client_socket, buffer, 1024);
        if (val_read == -1) {
            std::cerr << "Error reading from client" << std::endl;
        }
        temp += buffer;
        while ((index = temp.find("\r\n")) != std::string::npos) {
          sub_str = temp.substr(0, index) + "\n";
          matrix += sub_str;
          temp = temp.substr(index+2);
          if ((index = temp.find("end")) != std::string::npos) {
            stop_loop = true;
            temp = temp.substr(0, index);
          }
        }
    } while (!stop_loop);
    matrix += "end";
    if (MatrixHashTable::get_instance()->does_matrix_exist(matrix)) {
      matrix_name = MatrixHashTable::get_instance()->get_matrix_name(matrix);
      if(this->cache_manager_->exist_in_cache(matrix_name)) {
        solution = this->cache_manager_->get(matrix_name);
      } else {
        std::cout << "something went wrong, matrix exists but not saved";
      }
    }
    else {
        MatrixProblem matrix_p(matrix);
        MatrixSolution matrix_solution = solver_->solve(&matrix_p);
        matrix_solution.edit_solution_representation();
        solution = matrix_solution.get_solution();
        this->cache_manager_->save(matrix_p.get_name(), solution);
    }

    int val_write = send(client_socket, solution.c_str(), solution.length(), 0);
    if (val_write == -1) {
      std::cerr << "Error writing to client" << std::endl;
    }

}