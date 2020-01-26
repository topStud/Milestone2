//
// Created by topaz on 15/01/2020.
//

#ifndef MILESTONE2__STATE_H_
#define MILESTONE2__STATE_H_

#include <cmath>
#include <limits>
/**
 * a class that responsible for keeping
 * information of the nodes of the Searcher problem.
 * @tparam T
 */
template <typename T>
class State {
  const T id;
  const double value;
  double cost;
  double heuristic_cost;
  State<T>* parent;
  int row;
  int col;
  int degree;
 public:
  /**
   * constructor of the class. initializes the fields of the class.
   */
  State(T id, double val,int row, int col, int degree) : id(id), value(val), row(row), col(col), degree(degree), cost(std::numeric_limits<double>::infinity()) {}

  /**
   * get_id function
   * @return identifier of the node
   */
  T get_id () {return id;}

  /**
   * get_row function
   * @return the row of the cell in matrix
   */
  int get_row(){ return row;}

  /**
   * get_col function
   * @return the col of the cell in matrix
   */
  int get_col(){ return col;}

  /**
   * get_degree function
   * @return the col of the cell in matrix
   */
  int get_degree() { return degree;}

  /**
   * get_value function
   * @return the value of the node
   */
  double get_value() {return value;}

  /**
   * set_parent function.
   * @param s -parent state
   */
  void set_parent(State<T> *s) {parent = s;}

  /**
   * get_parent function
   * @return parent of the current state
   */
  State<T>* get_parent() {return parent;}

  /**
   * set_cost function
   * @param path_cost - the cost of the path till the current state.
   */
  void set_cost(double path_cost) {cost = path_cost;}

  /**
   * get_cost function
   * @return the cost of the path till the current state.
   */
  double get_cost() { return cost;}

  /**
   * set_heuristic_cost function.
   * @param heuristic_path_cost
   */
  void set_heuristic_cost(double heuristic_path_cost) {heuristic_cost = heuristic_path_cost;}

  /**
   * get_heuristic_cost function.
   * @return heuristic_cost
   */
  double get_heuristic_cost() { return heuristic_cost;}

  /**
   * operator== function
   * @param state - the state we compare the current state to.
   * @return returns true if equal, false otherwise.
   */
  bool operator==(State<T>* state) {
      return this->id == state->get_id();
  }
};

#endif //MILESTONE2__STATE_H_
