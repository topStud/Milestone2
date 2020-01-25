//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__MATRIXSOLVEROA_H_
#define MILESTONE2__MATRIXSOLVEROA_H_

#include <string>
#include <utility>

#include "MatrixSolution.h"
#include "Solver.h"
#include "MatrixProblem.h"
#include "Searcher.h"
#include "Solution.h"

class MatrixSolverOA : public Solver<Searchable<double>, MatrixSolution> {
  Searcher<double>* searcher_;
  int nodes_num;
 public:
  explicit MatrixSolverOA(Searcher<double>* searcher) : searcher_(searcher), nodes_num(0) {}
  MatrixSolution solve(Searchable<double>* searchable) override;
  int get_number_of_nodes_evaluated() override {return nodes_num;}
  std::string get_name() override {return searcher_->get_name();}
};

#endif //MILESTONE2__MATRIXSOLVEROA_H_