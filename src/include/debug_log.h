#ifndef DEBUG_LOG_HH
#define DEBUG_LOG_HH

#include <graph.h>
#include <stack>

// utilities for debugging

#ifdef GRAPH_DEBUG

/* print a stack of vertices. Useful for dfs debugging, use wisely*/
void print_stack(std::stack<vertex> p_stack)
{
    std::cout << '{';
    while (not p_stack.empty())
    {
        std::cerr << p_stack.top();
        std::cout << ", ";
        p_stack.pop();
    }
    std::cout << '}';
}

/* print and edge to the std output channel*/
std::ostream& operator<<(std::ostream& out, const edge& p_edge)
{
    out << '(' << p_edge.first << ", " << p_edge.second << ')';
    return out;
}

/* print the "adjacents" to the std output channel*/
std::ostream& operator<<(std::ostream& out, const std::list<vertex>& p_adjacents)
{
    for (const auto adjacents : p_adjacents)
        out << adjacents << " ";
    return out;
}
#endif //GRAPH_DEBUG

#endif  //END OF DEBUG_LOG_HH
