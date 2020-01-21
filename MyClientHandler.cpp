//
// Created by topaz on 14/01/2020.
//

#include "MyClientHandler.h"
#include "BestFirstSearch.h"
#include "DFS.h"

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
        DFS<double> b;
        MatrixSolverOA solver(&b);
        MatrixSolution matrix_solution = solver.solve(&matrix_p);
        matrix_solution.edit_solution_representation();
        solution = matrix_solution.get_solution();
        this->cache_manager_->save(matrix, solution);
    }

    int val_write = write(client_socket, buffer, 1024);
    if (val_write == -1) {
      std::cerr << "Error writing to client" << std::endl;
    }

}