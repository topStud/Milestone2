//
// Created by topaz on 20/01/2020.
//

#include "MatrixSolution.h"
void MatrixSolution::edit_solution_representation() {
  // here changes the solution field
  State<double> goal_state = state_list.back();
  State<double>* parent_state = goal_state.get_parent();
  std::string result = recursion_path(parent_state);
  this->solution = result.substr(0, result.length() - 2);
}

std::string MatrixSolution::recursion_path(State<double> *state) {
  std::string  str{}, direction{};
  // parent of the initiate state
  if (state == nullptr) {
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
  return recursion_path((*state).get_parent()) + direction + " (" + std::to_string((*state).get_cost()) + ") ,";
}