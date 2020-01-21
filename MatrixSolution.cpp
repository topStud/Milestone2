//
// Created by topaz on 20/01/2020.
//

#include "MatrixSolution.h"
void MatrixSolution::edit_solution_representation() {
  std::string result = recursion_path(this->state_);
  this->solution = result.substr(0, result.length() - 2);
}

std::string MatrixSolution::recursion_path(State<double> *state) {
  std::string  str{}, direction{};
  // parent of the initiate state
  if (state->get_parent() == nullptr) {
    return str;
  }
  // parent is at the left
  if (state->get_parent()->get_id() == state->get_id() - 1) {
    direction = RIGHT;
  }
  // parent is at the left
  else if (state->get_parent()->get_id() == state->get_id() + 1) {
    direction = LEFT;
  }
  // parent is above
  else if (state->get_parent()->get_id() < state->get_id()) {
    direction = DOWN;
  }
  // parent is underneath
  else {
    direction = UP;
  }
  return recursion_path((*state).get_parent()) + direction + " (" + std::to_string((int)(*state).get_cost()) + ") ,";
}