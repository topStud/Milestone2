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
  std::unordered_map<T, State<T>*> finished_nodes;
  std::stack<State<T>*> stack_nodes;

  void release_finished_nodes(State<T>* node)
  {
    State<T>* tmp_node = node;
    while(tmp_node != nullptr) {
      for (std::pair<T, State<T> *> element : finished_nodes) {
        if (element.first == tmp_node->get_id())
        {
          finished_nodes.erase(tmp_node->get_id());
          break;
        }
      }
      tmp_node = tmp_node->get_parent();
    }
    for (std::pair<T, State<T>*> element : finished_nodes) {
      delete element.second;
    }
    finished_nodes.clear();
  }

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
      if ((*node) == s.get_goal()) {
        // releasing stack nodes
        while (!stack_nodes.empty()) {
          delete stack_nodes.top();
          stack_nodes.pop();
        }
        release_finished_nodes(node);
        return node;
      }
      stack_nodes.pop();
      if (finished_nodes.find(node->get_id()) == finished_nodes.end()) {
        nodes_num++;
        finished_nodes.insert({node->get_id(), node});
        successors = s.create_successors(node);
        for (State<T>* c : successors) {
          if (finished_nodes.find(c->get_id()) == finished_nodes.end()) {
            stack_nodes.push(c);
          }
        }
      }
    }
    return nullptr;
  }

  /*~DFS() {
    while (!stack_nodes.empty()) {
      delete stack_nodes.top();
      stack_nodes.pop();
    }
    for (std::pair<T, State<T>*> element :finished_nodes) {
      delete element.second;
    }
  }*/
};

#endif //MILESTONE2__DFS_H_
