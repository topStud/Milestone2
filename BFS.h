//
// Created by sigalit on 23.1.2020.
//

#ifndef MILESTONE2_BFS_H
#define MILESTONE2_BFS_H

#include "BestFirstSearch.h"

/**
 * BFS class
 * the class is a searcher.
 * inherits the functionality of the BestFirstSearch class.
 * @tparam T
 */
template <typename T>
class BFS : public BestFirstSearch<T>{
    typedef std::pair<T, State<T>*> pair;

protected:
  /**
   * getCompareFunction function determines
   * the compare function the algorithm will use.
   * @return the compare function.
   */
    virtual std::function<bool(pair,pair)> getCompareFunction() override
    {
        return [](pair eLeft, pair eRight){
            return eLeft.second->get_degree() <= eRight.second->get_degree();
        };
    }
 public:
  /**
   * get_name function.
   * @return name of the algorithm.
   */
  std::string get_name() override {
    return "BFS_";
  }
};


#endif //MILESTONE2_BFS_H
