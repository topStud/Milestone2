//
// Created by sigalit on 19.1.2020.
//

#ifndef MILESTONE2_MAIN_H
#define MILESTONE2_MAIN_H

#include "BestFirstSearch.h"
#include "MatrixProblem.h"
#include "MatrixSolution.h"
#include "MatrixSolverOA.h"
#include "BFS.h"
#include "Server.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "FileCacheManager.h"
#include "MyParallelServer.h"

namespace boot {

    class Main {
    public:
        int main(int argc, char *argv[]);
    };

}

#endif //MILESTONE2_MAIN_H
