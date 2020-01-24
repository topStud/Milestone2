
#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H

#include <queue>
#include <functional>
#include <map>
#include <unordered_map>
#include "Searcher.h"
#include <iostream>

template <typename T>
class BestFirstSearch : public Searcher<T>{

    typedef std::pair<T, State<T>*> pair;
    typedef typename std::map<pair, T>::iterator Iterator;
private:
    int m_evaluatedNodes;
    std::unordered_map<T, State<T>*> closed;
    Iterator iter;

protected:
    virtual std::function<bool(pair,pair)> getCompareFunction()
    {
        return [](pair eLeft, pair eRight){ return eLeft.second->get_cost() <= eRight.second->get_cost();};
    }

    void releaseClosedMap(State<T>* node)
    {
        State<T>* tmp_node = node;
        while(tmp_node != nullptr) {
            for (std::pair<T, State<T> *> element : closed) {
                if (element.first == tmp_node->get_id())
                {
                    closed.erase(tmp_node->get_id());
                    break;
                }
            }
            tmp_node = tmp_node->get_parent();
        }
        for (std::pair<T, State<T>*> element : closed) {
            delete element.second;
        }
        closed.clear();
    }


public:

    BestFirstSearch(): m_evaluatedNodes(0) {}

    State<T>* search(Searchable<T>& s) override {
        auto func = getCompareFunction();
        std::map<pair, T, decltype(func)> openList(func);
        State<T>* init_state = s.get_init_state();
        openList.insert({{init_state->get_id(), init_state} , init_state->get_id()});
        State<T>* node;
        while (!openList.empty())
        {
            iter = openList.begin();
            node = iter->first.second;
            openList.erase(iter);
            m_evaluatedNodes++;
            closed.insert({node->get_id(), node});

            if(*node==s.get_goal())
            {
                // todo - add new function to remove all nodes of the solution path from closed map, then,
                //  delete the rest of the nodes from openList and closed and clear both maps
                for (std::pair<pair,T> element : openList) {
                    delete element.first.second;
                }
                openList.clear();
                releaseClosedMap(node);
                return node;
            }
            std::vector<State<T>* > successors = s.create_successors(node);
            for (State<T> *c : successors)
            {
                bool in_openList = false;
                iter = openList.begin();
                while (iter != openList.end())
                {
                    if(iter->first.first == c->get_id())
                    {
                        in_openList = true;
                        break;
                    }
                    ++iter;
                }
                bool in_closed = closed.find(c->get_id()) != closed.end();
                if(!in_closed && !in_openList)
                {
                    openList.insert({{c->get_id(), c}, c->get_id()});
                }
                else
                {
                    if (in_openList && !func(iter->first, {c->get_id(),c})) {
                        openList.erase(iter);
                        openList.insert({{c->get_id(), c},c->get_id()});
                        delete iter->first.second;
                    }
                    else
                    {
                        delete c;
                    }
                }
            }
        }
        std::cout<<"Not Found!"<<std::endl;
        return NULL;
    }

    int getNumberOfNodesEvaluated() { return m_evaluatedNodes;}

};


#endif //MILESTONE2_BESTFIRSTSEARCH_H
