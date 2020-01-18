//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__MATRIXSOLVEROA_H_
#define MILESTONE2__MATRIXSOLVEROA_H_

#include <string>
#include <utility>

#include "Solver.h"
#include "MatrixProblem.h"
#include "Searcher.h"
#include "Solution.h"

class MatrixSolverOA : public Solver<Searchable<double>, Solution<std::string>> {
  Searchable<double>* searchable_;
  Searcher<double>* searcher_;
 public:
  explicit MatrixSolverOA(Searcher<double>* searcher, Searchable<double>* searchable) : searcher_(searcher), searchable_(searchable) {}
  Solution<std::string>* solve(Searchable<double>* searchable) override;
};

#endif //MILESTONE2__MATRIXSOLVEROA_H_
