//
// Created by topaz on 14/01/2020.
//

#include "MyClientHandler.h"

void MyClientHandler::handle_client(int client_socket) {
    char buffer[1024] = "";
    std::string matrix{}, temp{}, solution{};

    while (strcmp(buffer, "end") != 0) {
        int val_read = read(client_socket, buffer, 1024);
        if (val_read == -1) {
            std::cerr << "Error reading from client" << std::endl;
        }
        if (strcmp(buffer, "end") == 0) {
            temp = buffer;
            matrix += temp;
        }
    }

    if(this->cache_manager_->exist_in_cache(matrix)) {
        solution = this->cache_manager_->get(matrix);
    } else {
        MatrixProblem matrix_p(matrix);
        // MatrixSolverOA solver(searcher, searchable - matrix_p);
        //this->cache_manager_->save(matrix, solution)
    }
    //send solution to client - todo

}