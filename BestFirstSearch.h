
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
    typedef typename std::map<pair, State<T>*>::iterator Iterator;
private:
    int m_evaluatedNodes;
    std::unordered_map<T, State<T>*> closed;
    Iterator iter;

public:

    BestFirstSearch(): m_evaluatedNodes(0) {}

    virtual std::function<bool(pair,pair)> getCompareFunction()
    {
        return [](pair eLeft, pair eRight){ return eLeft.second->get_cost() < eRight.second->get_cost();};
    }

    State<T>* search(Searchable<T>& s) override {
        std::pair<int,int> max_row= {0,0},max_col = {0,0};
        auto func = getCompareFunction();

        std::map<pair, State<T>*,decltype(func)> openList(func);
        State<T>* init_state = s.get_init_state();
        openList[{init_state->get_id(), init_state}]=init_state;
        State<T>* node;
        while (!openList.empty())
        {
            iter = openList.begin();
            node = iter->second;
            openList.erase(iter);
            m_evaluatedNodes++;
            closed[node->get_id()] = node;
            std::cout<<"Current node: "<< node->get_id()<<" - "<<node->get_row()<<","<<node->get_col()<<std::endl;
            if(max_row.first<node->get_row())
            {
                max_row = {node->get_row(), node->get_col()};
            }
            if(max_col.second<node->get_col())
            {
                max_col = {node->get_row(), node->get_col()};
            }
            if(*node==s.get_goal())
            {
                // todo - add new function to remove all nodes from the solution path from closed map, then,
                //  delete the rest of the nodes from openList and closed and clear both maps
                return node;
            }
            std::vector<State<T>* > successors = s.create_successors(node);
            std::cout<<"Num Of Successors found: "<< successors.size() <<std::endl;
            for (State<T> *c : successors)
            {
                std::cout<<"Successsor: "<< c->get_row()<<","<<c->get_col() <<std::endl;
                if(c->get_id() == 1252)
                {
                    std::cout<<"WHYYYYYYYYYY"<< std::endl;

                }
                //std::pair<bool, typename std::map<pair, State<T>*>::iterator> p = findPosInList(openList, c->get_id());
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
                if(in_closed){
                    std::cout<<"Already in closed: "<< c->get_id()<<std::endl;
                }

                if(!in_closed && !in_openList)
                {
                    auto pair_key = std::make_pair(c->get_id(), c);
                    openList[pair_key] = c;
                }
                else
                {
                    if(in_openList)
                    {
                        std::cout<<"Already in OpenList: "<< c->get_id()<<std::endl;
                        if (iter->second->get_cost() >= c->get_cost()) {
                            openList.erase(iter);
                            openList[std::make_pair(c->get_id(), c)] = c;
                        }
                    }
                }
            }
        }
        std::cout<<"Max Col point: "<<max_col.first<<","<<max_col.second<<std::endl;
        std::cout<<"Max Row point: "<<max_row.first<<","<<max_row.second<<std::endl;

        return NULL;
    }

    int getNumberOfNodesEvaluated() { return m_evaluatedNodes;}

};


#endif //MILESTONE2_BESTFIRSTSEARCH_H
/*
 * addToOpenList(searchable. getInitialState ()); // inherited from Searcher
HashSet<State> closed = new HashSet<State>();
while (OpenListSize > 0) {
State n = popOpenList(); // inherited from Searcher, removes the best state
closed.Add(n);
if (n.Equals(searchable. getIGoallState ()))
return backTrace(); // private method, back traces through the parents
// calling the delegated method, returns a list of states with n as a parent
List<State> succerssors = searchable. getAllPossibleStates(n);
foreach (State s in succerssors)
{
if (!closed.Contains(s) && !openContaines(s))
{
// s.setCameFrom(n); // already done by getSuccessors
addToOpenList(s);
}
else
{
//...
 *
def best_first_graph_search(problem, source, target, f):
    estimated_cost = tools.compute_distance(problem[source].lat, problem[source].lon,
                                            problem[target].lat, problem[target].lon) / 110
    node = Node(source, cost_to_target=estimated_cost, goal=target)
    frontier = PriorityQueue(f)  # Priority Queue
    frontier.append(node)
    closed_list = set()
    while frontier:
        node = frontier.pop()
        if node.state == target:
            return node.solution(), node.path_cost, estimated_cost
        closed_list.add(node.state)
        for child in node.expand(problem):
            if child.state not in closed_list and child not in frontier:
                frontier.append(child)
            elif child in frontier and f(child) < frontier[child]:
                del frontier[child]
                frontier.append(child)
    return None
 */