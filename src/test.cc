/**
 * @file test.cc
 * @author kate (zanetty54@gmail.com)
 * @brief 
 * @version 1.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//SIMPLE FILE TO TEST GRAPH FEATURES
//compile:  
//g++ -std=c++20 -Wall -Wextra -Wpedantic -o main test.cc -I . -D GRAPH_DEBUG
//COMPILE COMMAND WITH GCC
#include <debug_log.h>
#include <iostream>
#include <graph.h>

#define GRAPH_SIZE  7

/*sample graph*/
std::vector<edge> graph_sample = {
    {1,2}, {1,3}, {1,4},
    {2,1}, {2, 5},
    {3,6},
    {4,1}
};


int main(int, char**)
{
    graph myGraph;

    std::cout << myGraph.size() << std::endl;
    std::cout << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    myGraph = graph(GRAPH_SIZE);
    for (const auto& _edges : graph_sample)
        myGraph.add_edge(_edges);

    std::cout << "This line comes after insertion of few edges into graph" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << myGraph.size() << std::endl;
    std::cout << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    std::cout << "we print the graph" << std::endl;
    std::cout << myGraph << std::endl;

    std::cin.get();
    return EXIT_SUCCESS;
}