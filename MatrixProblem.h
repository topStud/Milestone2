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
class MatrixProblem : public Searchable<double>{
    std::vector<std::vector<double>> matrix;
    State<double>* init_state;
    State<double>* goal_state;
    int rows;
    int cols;
    std::string name;
    void matrix_from_str(const std::string& str);
    static bool is_number(const std::string& str);
public:
    static int counter;
    explicit MatrixProblem(const std::string& matrix);
    State<double>* get_init_state() override;
    State<double>* get_goal() override;
    std::string get_name() override;
    std::vector<State<double>*> create_successors(State<double>* current_state) override;
};

#endif //MILESTONE2__MATRIXPROBLEM_H_