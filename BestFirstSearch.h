
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

private:
    int m_evaluatedNodes;
    std::unordered_map<T, State<T>*> closed;
    typename std::map<T, State<T>*>::iterator iter;


public:

    BestFirstSearch(): m_evaluatedNodes(0) {}

    virtual std::function<bool(State<T>*,State<T>*)> getCompareFunction()
    {
        return [](State<T>* nLeft, State<T>* nRight){ return nLeft->get_cost() > nRight->get_cost();};
    }

    State<T>* search(Searchable<T>& s) override {
        auto func = getCompareFunction();
        std::map<T, State<T>*,decltype(func)> openList;
        State<T>* init_state = s.get_init_state();
        openList[init_state->get_id()]=init_state;
        State<T>* node;
        while (!openList.empty())
        {
            iter = openList.begin();
            node = iter->second;
            openList.erase(iter);
            m_evaluatedNodes++;
            closed[node->get_id()] = node;
            if(*node==s.get_goal())
            {
                // todo - add new function to remove all nodes from the solution path from closed map, then,
                //  delete the rest of the nodes from openList and closed and clear both maps
                return node;
            }
            std::vector<State<T>* > successors = s.create_successors(node);
            for (State<T> *c : successors)
            {
                if(closed.find(c->get_id()) == closed.end() && openList.find(c->get_id()) == openList.end())
                {
                    openList[c->get_id()] = c;
                }
                else
                {
                    iter = openList.find(c->get_id());
                    if(iter != openList.end()) {
                        if (iter != openList.end() && func(iter->second, c)) {
                            openList.erase(iter);
                            openList[c->get_id()] = c;
                        }
                    }
                }
            }
        }
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