//
// Created by topaz on 12/01/2020.
//

#ifndef MILESTONE2__SOLVER_H_
#define MILESTONE2__SOLVER_H_

/**
 * solver interface
 * @tparam Problem
 * @tparam Solution
 */
template <typename Problem, typename Solution>
class Solver {
 public:
  virtual Solution solve(Problem* problem) = 0;
  virtual int get_number_of_nodes_evaluated() = 0;
  virtual std::string get_name() = 0;
};

#endif //MILESTONE2__SOLVER_H_
