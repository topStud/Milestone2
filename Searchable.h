//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__SEARCHABLE_H_
#define MILESTONE2__SEARCHABLE_H_

#include "State.h"
template <typename T>
class Searchable {
 public:
  virtual State<T> get_init_state() = 0;
  virtual State<T> get_goal() = 0;
  virtual std::vector<State<T>> create_successors(State<T> current_state) = 0;
};

#endif //MILESTONE2__SEARCHABLE_H_
