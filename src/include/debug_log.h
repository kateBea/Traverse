#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <graph.h>
#include <stack>

// utilities for debugging

#ifdef GRAPH_DEBUG

/*print a stack of vertices. Useful for dfs debugging, use wisely*/
void print_stack(std::stack<vertex> _stack)
{
    std::cout << '{';
    while (not _stack.empty())
    {
        std::cerr << _stack.top();
        std::cout << ", ";
        _stack.pop();
    }
    std::cout << '}';
}

/*print and edge to the std output channel*/
std::ostream& operator<<(std::ostream& _cout, const edge& _edge)
{
    std::cerr << '(' << _edge.first << ", " << _edge.second << ')';
    return _cout;
}

/*print the "adjacents" to the std output channel*/
std::ostream& operator<<(std::ostream& _cout, const std::list<vertex>& adjacents)
{
    for (const auto _adjacents : adjacents)
        std::cerr << _adjacents << " ";
    return _cout;
}
#endif //GRAPH_DEBUG

#endif  //END OF DEBUG_LOG_HH
