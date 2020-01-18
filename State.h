//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__STATE_H_
#define MILESTONE2__STATE_H_

#include <cmath>
template <typename T>
class State {
  const T identifier;
  const double value;
  double cost;
  State<T>* prior;
 public:
  State(T id, double val) : identifier(id), value(val), cost(std::numeric_limits<double>::infinity()) {}
  int get_id () {return identifier;}
  T get_value() {return value;}
  void set_prior(State<T> former) {prior = former;}
  void set_cost(double path_cost) {cost = path_cost;}
  bool operator==(State<T> state) {return this->identifier == state.get_id();}
};

#endif //MILESTONE2__STATE_H_
