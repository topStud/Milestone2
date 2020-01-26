//
// Created by sigalit on 23.1.2020.
//

#ifndef MILESTONE2_ASTAR_H
#define MILESTONE2_ASTAR_H

#include "BestFirstSearch.h"

/**
 * A* class
 * the class is a searcher.
 * inherits the functionality of the BestFirstSearch class.
 * @tparam T
 */
template <typename T>
class Astar : public BestFirstSearch<T>{
    typedef std::pair<T, State<T>*> pair;

protected:
    /**
     * getCompareFunction function determines
     * the compare function the algorithm will use.
     * @return the compare function.
     */
    std::function<bool(pair,pair)> getCompareFunction() override
    {
        return [](pair eLeft, pair eRight){
            return eLeft.second->get_cost() + eLeft.second->get_heuristic_cost() <=
            eRight.second->get_cost() + eRight.second->get_heuristic_cost();
        };
    }
 public:
  /**
   * get_name function.
   * @return name of the algorithm.
   */
  std::string get_name() override {
    return "AStar_";
  }
};

#endif //MILESTONE2_ASTAR_H
