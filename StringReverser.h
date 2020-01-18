#ifndef MILESTONE2_STRINGREVERSER_H
#define MILESTONE2_STRINGREVERSER_H

#include <string>
#include <algorithm>
#include "Solver.h"


class StringReverser: public Solver<std::string,std::string> {
public:
    virtual std::string solve(std::string problem);
};


#endif //MILESTONE2_STRINGREVERSER_H
