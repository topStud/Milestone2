//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__SEARCHER_H_
#define MILESTONE2__SEARCHER_H_

#include <list>
#include "Searchable.h"
#include "State.h"

template <typename T>
class Searcher {
 public:
    virtual State<T>* search(Searchable<T>& s) = 0;
    virtual int getNumberOfNodesEvaluated()= 0;
};

#endif //MILESTONE2__SEARCHER_H_