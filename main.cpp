//
// Created by sigalit on 19.1.2020.
//

#include "Main.h"

/**
 * the starting function of the program.
 * calls to the main created for the boot namespace
 * @param argc - number of arguments.
 * @param argv - array of strings - command line arguments.
 * @return 0 - if the program finished successfully.
 */
int main(int argc, char *argv[]) {

    boot::Main start;
    return start.main(argc,argv);
}