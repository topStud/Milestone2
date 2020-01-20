//
// Created by topaz on 20/01/2020.
//

#include "MatrixSolverOA.h"
MatrixSolution MatrixSolverOA::solve(Searchable<double>* searchable) {
  MatrixSolution solution(searcher_->search(*searchable));
  nodes_num = searcher_->getNumberOfNodesEvaluated();
  return solution;
}
