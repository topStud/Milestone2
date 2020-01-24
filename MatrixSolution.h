//
// Created by topaz on 20/01/2020.
//

#ifndef MILESTONE2__MATRIXSOLUTION_H_
#define MILESTONE2__MATRIXSOLUTION_H_

#include <list>
#include <utility>
#include "Solution.h"
#include "State.h"

#define LEFT "Left"
#define RIGHT "Right"
#define UP "Up"
#define DOWN "Down"

class MatrixSolution : Solution<std::string> {
  State<double>* state_;
  std::string solution;
  std::string recursion_path(State<double>* state);
  void release_solution();
public:
  explicit MatrixSolution(State<double>* state) : state_(state) {}
  void edit_solution_representation() override;
  std::string get_solution() override { return solution;}
};

#endif //MILESTONE2__MATRIXSOLUTION_H_
