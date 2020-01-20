//
// Created by topaz on 20/01/2020.
//

#ifndef MILESTONE2__MATRIXSOLUTION_H_
#define MILESTONE2__MATRIXSOLUTION_H_

#include <list>
#include <utility>
#include "Solution.h"
#include "State.h"

class MatrixSolution : Solution<std::string> {
  std::list<State<double>> state_list;
  std::string solution;
 public:
  explicit MatrixSolution(std::list<State<double>> list) : state_list(std::move(list)) {}
  void edit_solution_representation() override;
  std::string get_solution() override { return solution;}
};

#endif //MILESTONE2__MATRIXSOLUTION_H_
