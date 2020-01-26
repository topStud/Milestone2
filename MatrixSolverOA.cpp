//
// Created by topaz on 20/01/2020.
//

#include "MatrixSolverOA.h"

/**
 * solve function.
 * calls to the search algorithm of the searcher and returns the solution.
 * @param searchable
 * @return solution represented in string.
 */
MatrixSolution MatrixSolverOA::solve(Searchable<double>* searchable) {
  State<double >* st = searcher_->search(*searchable);
  MatrixSolution solution(st);
  nodes_num = searcher_->getNumberOfNodesEvaluated();
  delete searchable->get_goal();
  return solution;
}
