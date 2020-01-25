//
// Created by topaz on 14/01/2020.
//

#ifndef MILESTONE2__MYCLIENTHANDLER_H_
#define MILESTONE2__MYCLIENTHANDLER_H_

#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

#include "MatrixProblem.h"
#include "MatrixSolverOA.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include "BestFirstSearch.h"
#include "MatrixHashTable.h"

class MyClientHandler : public ClientHandler{
    Solver<Searchable<double>, MatrixSolution>* solver_;
    CacheManager<std::string>* cache_manager_;
public:
    MyClientHandler(Solver<Searchable<double>, MatrixSolution>* solver, CacheManager<std::string>* cache) : solver_(solver), cache_manager_(cache) {}
    void handle_client( int client_socket) override;
};

#endif //MILESTONE2__MYCLIENTHANDLER_H_