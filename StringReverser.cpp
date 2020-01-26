#include "StringReverser.h"

/**
 * solve function.
 * @param problem  - the string from the client.
 * @return the reversed string.
 */
std::string StringReverser::solve(std::string problem)
{
    std::reverse(problem.begin(), problem.end());
    return problem;
}