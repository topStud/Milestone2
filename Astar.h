//
// Created by sigalit on 23.1.2020.
//

#ifndef MILESTONE2_ASTAR_H
#define MILESTONE2_ASTAR_H

#include "BestFirstSearch.h"
template <typename T>
class Astar : public BestFirstSearch<T>{

    typedef std::pair<T, State<T>*> pair;

protected:
    virtual std::function<bool(pair,pair)> getCompareFunction() override
    {
        return [](pair eLeft, pair eRight){
            return eLeft.second->get_cost() + eLeft.second->get_heuristic_cost() <=
            eRight.second->get_cost() + eRight.second->get_heuristic_cost();
        };
    }

};

#endif //MILESTONE2_ASTAR_H
