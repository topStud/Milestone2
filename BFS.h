//
// Created by sigalit on 23.1.2020.
//

#ifndef MILESTONE2_BFS_H
#define MILESTONE2_BFS_H

#include "BestFirstSearch.h"
template <typename T>
class BFS : public BestFirstSearch<T>{

    typedef std::pair<T, State<T>*> pair;

protected:
    virtual std::function<bool(pair,pair)> getCompareFunction() override
    {
        return [](pair eLeft, pair eRight){
            return eLeft.second->get_degree() <= eRight.second->get_degree();
        };
    }

};


#endif //MILESTONE2_BFS_H
