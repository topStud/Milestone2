//
// Created by topaz on 15/01/2020.
//

#include "MatrixProblem.h"

/**
 * get_init_state function.
 * @return init state - the node we are told to start with.
 */
State<double>* MatrixProblem::get_init_state() {
    return this->init_state;
}

/**
 * get_goal function.
 * @return goal state - the node we are told to reach at the end.
 */
State<double>* MatrixProblem::get_goal() {
    return this->goal_state;
}

/**
 * constructor, initializes the fields and adds matrix to the matrix collection.
 * sends the matrix to be converted from a string to a vector of vectors structure.
 * @param matrix - a string that represents a matrix.
 */
MatrixProblem::MatrixProblem(const std::string& matrix) {
  init_state = nullptr;
  goal_state = nullptr;
  rows = 0;
  cols = 0;
  matrix_from_str(matrix);
  MatrixHashTable::get_instance()->add_to_table(matrix);
}

/**
 * matrix_from_str function.
 * reads each line of the string and converts the line to a vector of numbers.
 * the three last lines represent - 1) initial location in matrix.
 *                                  2) goal location in matrix.
 *                                  3) the word "end"
 * @param string - a string that represents a matrix.
 */
void MatrixProblem::matrix_from_str(const std::string& string) {
    int init_row, init_col, goal_row, goal_col, count_rows = -3;
    std::vector<double> vec;
    std::string row_str{}, node{};
    std::stringstream ss1(string);

    while (getline(ss1, row_str, '\n')) {
        count_rows++;
        std::stringstream ss2(row_str);
        while(getline(ss2, node, ',')) {
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

/**
 * create_successors function.
 * creates states according to the current given node - neighbors.
 * @param current_state - the node given - current cell in the matrix.
 * @return a vector of the neighbors.
 */
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

    for (auto & i : vec) {
        i->set_parent(current_state);
        i->set_cost(current_state->get_cost() + i->get_value());
        i->set_heuristic_cost(abs(i->get_row()-goal_state->get_row()) +
        abs(i->get_col()-goal_state->get_col()));
    }
    return vec;
}
