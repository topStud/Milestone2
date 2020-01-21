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
 public:
  DFS() : nodes_num(0) {}

  int getNumberOfNodesEvaluated() override { return nodes_num;}

  State<T>* search(Searchable<T>& s) override {
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
        nodes_num++;
        finished_nodes.insert({node->get_id(), node});
        successors = s.create_successors(*node);
        for (State<T>* c : successors) {
          if (finished_nodes.find(c->get_id()) == finished_nodes.end()
            && c->get_value() != std::numeric_limits<double>::infinity()) {
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
