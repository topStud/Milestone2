//
// Created by topaz on 20/01/2020.
//

#include "MatrixSolution.h"

/**
 * edit_solution_representation function.
 * responsible for the representation of the matrix solution.
 * calls the recursion function.
 */
void MatrixSolution::edit_solution_representation() {
  if (this->state_ != nullptr) {
    std::string result = recursion_path(this->state_);
    release_solution();
    this->solution = result.substr(0, result.length() - 2);
    this->solution += '\n';
  } else {
    this->solution = "There is no path that can reach the target";
  }
}

/**
 * release_solution function.
 * after the solution is available, we release the memory
 * occupied the the nodes of the path that the algorithm found.
 */
void MatrixSolution::release_solution() {
    State<double> *tmp = this->state_->get_parent();
    while (tmp != nullptr) {
        delete this->state_;
        this->state_ = tmp;
        tmp = tmp->get_parent();
    }
    delete this->state_;

}

/**
 * recursion function for translating the solution from a vector of stated tto a string.
 * @param state - the goal state.
 * @return returns a string representation of the path.
 */
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
  return recursion_path((*state).get_parent()) + direction + " (" + std::to_string((double)(*state).get_cost()) + ") ,";
}