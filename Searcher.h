//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__SEARCHER_H_
#define MILESTONE2__SEARCHER_H_

template <typename T>
class Searcher {
  virtual void search(Searchable<T> s) = 0;
};

#endif //MILESTONE2__SEARCHER_H_
