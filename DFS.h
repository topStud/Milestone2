//
// Created by topaz on 21/01/2020.
//

#ifndef MILESTONE2__DFS_H_
#define MILESTONE2__DFS_H_

#include <stack>
#include <unordered_map>
#include <algorithm>
#include "Searcher.h"
template <typename T>
class DFS : public  Searcher<T> {
  int nodes_num;
  std::unordered_map<int, State<T>*> finished_nodes;
  std::stack<State<T>*> stack_nodes;

  /*bool finished_list_contains(State<T>* state) {
    auto iter = finished_nodes.begin();
    while (iter != finished_nodes.end()) {
      if (**iter == *state)
        return true;
    }
    return false;
  }*/

  State<T>* recursion_dfs(Searchable<T>& s) {
   /* std::vector<State<T>*> successors;
    bool is_finished = false;
    State<T>* node = stack_nodes.top();
    if ((*node) == *s.get_goal()) {
      return node;
    }
    stack_nodes.pop();
    finished_nodes.push_back(node);
    successors = s.create_successors((*node));
    for (State<T>* state : successors) {
      for (State<T>* finished : finished_nodes) {
        if (finished->get_id() == state->get_id()) {
          is_finished = true;
          break;
        }
      }
      if (!is_finished) {
        is_finished = false;
        state->set_parent(node);
        state->set_cost(node->get_cost() + state->get_value());
        stack_nodes.push(state);
        recursion_dfs(s);
      }
    }*/
  }
 public:
  DFS() : nodes_num(0) {}

  int getNumberOfNodesEvaluated() override { return nodes_num;}

  State<T>* search(Searchable<T>& s) override {
    /*State<T>* init_state = s.get_init_state();
    stack_nodes.push(init_state);
    return recursion_dfs(s);*/
    State<T>* node;
    std::vector<State<T>*> successors;
    State<T>* init_state = s.get_init_state();
    stack_nodes.push(init_state);
    while (!stack_nodes.empty()) {
      node = stack_nodes.top();
      if ((*node) == *s.get_goal()) {
        return node;
      }
      stack_nodes.pop();
      if (finished_nodes.find(node->get_id()) == finished_nodes.end()) {
        finished_nodes.insert({node->get_id(), node});
        successors = s.create_successors(*node);
        for (State<T>* c : successors) {
          if (finished_nodes.find(c->get_id()) == finished_nodes.end()) {
            c->set_parent(node);
            c->set_cost(node->get_cost() + c->get_value());
            stack_nodes.push(c);
          }
        }
      }
    }
    int x;
    std::cout << "hgfm";
  }

  ~DFS() {
    while (!stack_nodes.empty()) {
      delete stack_nodes.top();
      stack_nodes.pop();
    }
    for (std::pair<int, State<T>*> element :finished_nodes) {
      delete element.second;
    }
  }
};

#endif //MILESTONE2__DFS_H_
