//
// Created by topaz on 15/01/2020.
//

#include "MatrixProblem.h"
State<double> MatrixProblem::get_init_state() {
  return *this->init_state;
}

State<double> MatrixProblem::get_goal() {
  return *this->goal_state;
}

void MatrixProblem::matrix_from_str(const std::string& string) {
  int row, col, count_rows = -3;
  std::vector<double> vec;
  std::string row_str{}, node{};
  std::stringstream ss1(string);

  while (getline(ss1, row_str, '\n')) {
    count_rows++;
    std::stringstream ss2(row_str);
    while(getline(ss2, node, ',')) {
      remove_if(node.begin(), node.end(), isspace);
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
  row = *vec.begin();
  col = vec.back();
  this->goal_state = new State<double>(row * this->cols + col + 1, this->matrix[row][col]);
  this->matrix.pop_back();
  vec = this->matrix.back();
  this->init_state = new State<double>(1, this->matrix[*vec.begin()][vec.back()]);
  this->matrix.pop_back();
}

std::vector<State<double>> MatrixProblem::create_successors(State<double> current_state) {
  std::vector<State<double>> vec;
  int id = current_state.get_id();
  // left
  if ((id % this-> cols) != 1) {
    State<double> temp(id - 1, this->matrix[(id - 1) / this->cols][(id - 1) % this->cols]);
    vec.push_back(temp);
  }
  // right
  if ((id % this->cols) != 0) {
    State<double> temp(id + 1, this->matrix[(id + 1) / this->cols][(id + 1) % this->cols]);
    vec.push_back(temp);
  }
  // up
  if ((id / (this->cols + 1)) != 0) {
    State<double> temp(id - this->cols, this->matrix[(id - this->cols) / this->cols][(id - this->cols) % this->cols]);
    vec.push_back(temp);
  }
  // down
  if ((id / this->cols) != this->rows) {
    State<double> temp(id + this->cols, this->matrix[(id + this->cols) / this->cols][(id + this->cols) % this->cols]);
    vec.push_back(temp);
  }
  return vec;
}