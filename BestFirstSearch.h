
#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H

#include <queue>
#include <functional>
#include <unordered_set>
#include <map>
#include "Searcher.h"

template <typename T>
class BestFirstSearch : public Searcher<T>{

private:
    int m_evaluatedNodes;

public:

    BestFirstSearch()
    {
        m_evaluatedNodes= 0;
    }
    virtual std::function<bool(State<T>&,State<T>&)> getCompareFunction()
    {
        return [](State<T>& nLeft, State<T>& nRight){ return nLeft.get_cost() > nRight.get_cost();};
    }

    /*State<double>* search(Searchable<T>& s)
    {
        auto func = getCompareFunction();
        std::map<T,State<T>> openList;
        typename std::map<T,State<T> >::iterator iter;
        openList.insert(std::pair<T,State<T> >(s.get_init_state().get_id(),s.get_init_state()));
        std::unordered_set<T> closed;
        while (!openList.empty())
        {
            iter = openList.begin();
            State<T> n = iter->second;
            openList.erase(iter);
            m_evaluatedNodes++;
            closed.insert(n.get_id());
            if(n==s.get_goal())
            {
                return &n;
            }
            std::vector<State<T> > successors = s.create_successors(n);
            for (State<T> c : successors)
            {
                if(closed.find(c.get_id()) == closed.end() && openList.find(c.get_id()) == openList.end())
                {
                    c.set_parent(&n);
                    c.set_cost(n.get_cost()+c.get_value());
                    openList.insert(std::pair<T,State<T> >(c.get_id(),c));
                }
                else
                {
                    iter = openList.find(c.get_id());
                    if(iter != openList.end() && func(iter->second, c))
                    {
                        openList.erase(iter);
                        openList.insert(std::pair<T,State<T> >(c.get_id(),c));
                    }
                }
            }
        }
        return NULL;
    }*/

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