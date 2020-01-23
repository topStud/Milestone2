//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__STATE_H_
#define MILESTONE2__STATE_H_

#include <cmath>
#include <limits>
template <typename T>
class State {
  const T id;
  const double value;
  double cost;
  double heuristic_cost;
  State<T>* parent;
  int row;
  int col;
 public:
  State(T id, double val,int row, int col) : id(id), value(val), row(row), col(col), cost(std::numeric_limits<double>::infinity()) {}
  T get_id () {return id;}
  int get_row(){ return row;}
  int get_col(){ return col;}
  double get_value() {return value;}
  void set_parent(State<T> *s) {parent = s;}
  State<T>* get_parent() {return parent;}
  void set_cost(double path_cost) {cost = path_cost;}
  double get_cost() { return cost;}
  void set_heuristic_cost(double heuristic_path_cost) {heuristic_cost = heuristic_path_cost;}
  double get_heuristic_cost() { return heuristic_cost;}
  bool operator==(State<T>* state) {
      return this->id == state->get_id();
  }
};

#endif //MILESTONE2__STATE_H_
