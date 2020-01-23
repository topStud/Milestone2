//
// Created by topaz on 15/01/2020.
//

#include <iostream>
#include "MatrixProblem.h"
State<double>* MatrixProblem::get_init_state() {
    return this->init_state;
}

State<double>* MatrixProblem::get_goal() {
    return this->goal_state;
}

void MatrixProblem::matrix_from_str(const std::string& string) {
    int init_row, init_col, goal_row, goal_col, count_rows = -3;
    std::vector<double> vec;
    std::string row_str{}, node{};
    std::stringstream ss1(string);

    while (getline(ss1, row_str, '\n')) {
        count_rows++;
        std::stringstream ss2(row_str);
        while(getline(ss2, node, ',')) {
            //remove_if(node.begin(), node.end(), isspace);
            node.erase(remove_if(node.begin(), node.end(), isspace), node.end());
            vec.push_back(strtod(node.c_str(), nullptr));
        }
        this->matrix.push_back(vec);
        vec.clear();
    }

    this->rows = count_rows;
    this->cols = this->matrix[0].size();

    // removes the last three - starting point, ending point and "end"
    this->matrix.pop_back();
    vec = this->matrix.back();
    goal_row = *vec.begin();
    goal_col = vec.back();
    this->goal_state = new State<double>(goal_row * this->cols + goal_col + 1, this->matrix[goal_row][goal_col], goal_row, goal_col, 0);
    this->goal_state->set_heuristic_cost(0);
    this->matrix.pop_back();
    vec = this->matrix.back();
    init_row = *vec.begin();
    init_col = vec.back();
    this->init_state = new State<double>(init_row * this->cols + init_col + 1, this->matrix[init_row][init_col],init_row,init_col, 0);
    this->matrix.pop_back();
    this->init_state->set_parent(nullptr);
    this->init_state->set_cost(this->init_state->get_value());
    this->init_state->set_heuristic_cost(abs(init_row-goal_row) + abs(init_col-goal_col));
}

std::vector<State<double>*> MatrixProblem::create_successors(State<double>* current_state) {
    std::vector<State<double>*> vec;
    double value;
    int id = current_state->get_id();
    int row,col;
    // left
    if ((id % this-> cols) != 1) {
        row = (id - 1) / this->cols;
        col = ((id - 1) % this->cols) - 1;
        value = this->matrix[row][col];

        if (value!=-1) {
            auto *temp = new State<double>(id - 1, value, row, col, current_state->get_degree()+1);
            vec.push_back(temp);
        }
    }
    // up
    if ((id / (this->cols + 1)) != 0) {
        row = (id - 1) / this->cols -1;
        col = (id - 1) % this->cols;
        value = this->matrix[row][col];

        if (value!=-1) {
            auto *temp = new State<double>(id - this->cols, value,row,col,current_state->get_degree()+1);
            vec.push_back(temp);
        }
    }
    // right
    if ((id % this->cols) != 0) {
        row = (id-1) / this->cols;
        col = ((id - 1) % this->cols) +1;
        value = this->matrix[row][col];

        if (value!=-1) {
            auto *temp = new State<double>(id + 1, value,row,col, current_state->get_degree()+1);
            vec.push_back(temp);
        }
    }
    // down
    if (((id - 1)/ this->cols) != this->rows - 1) {
        row = ((id - 1) / this->cols)+1;
        col = (id - 1) % this->cols;
        value = this->matrix[row][col];

        if (value!=-1) {
            auto *temp = new State<double>(id + this->cols, value,row,col, current_state->get_degree()+1);
            vec.push_back(temp);
        }
    }

    for (int i = 0; i < vec.size(); ++i) {
        vec[i]->set_parent(current_state);
        vec[i]->set_cost(current_state->get_cost() + vec[i]->get_value());
        vec[i]->set_heuristic_cost(abs(vec[i]->get_row()-goal_state->get_row()) +
        abs(vec[i]->get_col()-goal_state->get_col()));
    }
    return vec;
}
