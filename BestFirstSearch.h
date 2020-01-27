
#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H

#include <queue>
#include <functional>
#include <map>
#include <unordered_map>
#include "Searcher.h"
#include <iostream>

/**
 * BestFirstSearch class.
 * the class implements the searcher interface.
 * has an algorithm for finding the best path
 * from initial node to goal node.
 * @tparam T
 */
template <typename T>
class BestFirstSearch : public Searcher<T>{

    typedef std::pair<T, State<T>*> pair;
    typedef typename std::map<pair, T>::iterator Iterator;
private:
    int m_evaluatedNodes;
    std::unordered_map<T, State<T>*> closed;
    Iterator iter;

protected:
    /**
     * getCompareFunction function determines
     * the compare function the algorithm will use.
     * @return the compare function.
     */
    virtual std::function<bool(pair,pair)> getCompareFunction()
    {
        return [](pair eLeft, pair eRight){ return eLeft.second->get_cost() <= eRight.second->get_cost();};
    }

    /**
     * releaseClosedMap function.
     * removes all the nodes which are part of the best
     * path from the initial node to the goal- from the map.
     * and then releases the rest of nodes.
     * @param the gaol node.
     */
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
    /**
     * constructor function, initiates the node number.
     */
    BestFirstSearch(): m_evaluatedNodes(0) {}

    /**
     * search function.
     * finds the best path to the goal node.
     * @param s searchable.
     * @return the goal node.
     */
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
                    // the path of the node can be improved
                    if (in_openList && !func(iter->first, {c->get_id(),c})) {
                        openList.erase(iter);
                        delete iter->first.second;
                        openList.insert({{c->get_id(), c},c->get_id()});
                    }
                    else
                    {
                        // the node exists with a better path
                        delete c;
                    }
                }
            }
        }
        // returns null if the goal is unreachable.
        std::cout<<"Not Found!"<<std::endl;
        return NULL;
    }
    /**
     * getNumberOfNodesEvaluated function.
     * @return number of visited nodes during the search.
     */
    int getNumberOfNodesEvaluated() { return m_evaluatedNodes;}
    /**
     * get_name function.
     * @return name of the algorithm- BestFS.
     */
     virtual std::string get_name() {
      return "BestFirstSearch_";
    }

};


#endif //MILESTONE2_BESTFIRSTSEARCH_H
