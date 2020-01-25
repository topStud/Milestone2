//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__MATRIXPROBLEM_H_
#define MILESTONE2__MATRIXPROBLEM_H_

#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <regex>

#include "Searchable.h"
#include "State.h"
#include "MatrixHashTable.h"

class MatrixProblem : public Searchable<double>{
    std::vector<std::vector<double>> matrix;
    State<double>* init_state;
    State<double>* goal_state;
    int rows;
    int cols;
    void matrix_from_str(const std::string& str);
public:
    explicit MatrixProblem(const std::string& matrix);
    State<double>* get_init_state() override;
    State<double>* get_goal() override;
    std::vector<State<double>*> create_successors(State<double>* current_state) override;
};

#endif //MILESTONE2__MATRIXPROBLEM_H_