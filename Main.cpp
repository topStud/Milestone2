//
// Created by sigalit on 19.1.2020.
//

#include "Main.h"

#define DEFAULT_PORT 5600;
using namespace server_side;

/**
 * main function. manages the whole project.
 * receives up to 10 clients and handles them.
 * @param argc - number of arguments.
 * @param argv - array of strings- command line arguments.
 * @return 0 - if the program finished successfully.
 */
int boot::Main::main(int argc, char **argv) {
    int port_num;
    if (argc < 2) {
        port_num = DEFAULT_PORT;
    }
    else
    {
        // convert a string to integer
        char *temp;
        port_num = (int) strtol(argv[1], &temp, 10);
    }

    FileCacheManager<std::string> cache_manager;
    std::vector<ClientHandler*> client_handler_vec;
    std::vector<MatrixSolverOA*> solver_vec;
    std::vector<BestFirstSearch<double>*> best_f_s_vec;

    for (int j = 0; j < 10; ++j) {
        best_f_s_vec.push_back(new BestFirstSearch<double>());
        solver_vec.push_back(new MatrixSolverOA(best_f_s_vec[j]));
        client_handler_vec.push_back(new MyClientHandler(solver_vec[j], &cache_manager));
    }

    MyParallelServer myServer;
    myServer.open(port_num, client_handler_vec);

    std::this_thread::sleep_for(std::chrono::seconds(50000));
    for (int i = 0; i < client_handler_vec.size(); ++i) {
        delete best_f_s_vec[i];
        delete solver_vec[i];
        delete client_handler_vec[i];
    }

    MatrixHashTable::get_instance()->save_table();
    return 0;
}