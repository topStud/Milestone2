//
// Created by topaz on 14/01/2020.
//

#include "MyClientHandler.h"

/**
 * handle_client function responsible for the communication with the client.
 * reads from the client until the client sends the word "end".
 * checks if the solution for the clients problem exists.
 * if existed sends the saved solution, otherwise, solves the problem,
 * saves the solution and sends it to the client.
 * @param client_socket
 */
void MyClientHandler::handle_client(int client_socket) {
    std::regex r(".*[end]+\n?.*");
    char buffer[1025] = "";
    buffer[1024] = '\0';
    std::string matrix{}, temp{}, solution{}, sub_str{}, matrix_name{};
    bool stop_loop = false;
    int index;

    do {
        int val_read = read(client_socket, buffer, 1024);
        if (val_read == -1) {
            std::cerr << "Error reading from client" << std::endl;
        }
        temp += buffer;
        while ((index = temp.find('\n')) != std::string::npos) {
          sub_str = temp.substr(0, index+1);
          matrix += sub_str;
          temp = temp.substr(index+1);
          if (std::regex_match(sub_str, r)) {
            stop_loop = true;
            break;
          }
        }
        memset(buffer, 0 , sizeof(buffer));
    } while (!stop_loop);
    if (MatrixHashTable::get_instance()->does_matrix_exist(matrix)) {
      matrix_name = solver_->get_name() + MatrixHashTable::get_instance()->get_matrix_name(matrix);
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
        matrix_name = solver_->get_name() + MatrixHashTable::get_instance()->get_matrix_name(matrix);
        this->cache_manager_->save(matrix_name, solution);
    }

    int val_write = send(client_socket, solution.c_str(), solution.length(), 0);
    if (val_write == -1) {
      std::cerr << "Error writing to client" << std::endl;
    }

}