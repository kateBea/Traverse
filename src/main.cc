/**
 * @file main.cc
 * @author kate (zanetty54@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//compile:  
//g++ -std=c++20 -Wall -Wextra -Wpedantic -o main test_procedures.cc -I . -D GRAPH_DEBUG
#include <debug_log.h>
#include <procedures.h>
#include <cstdint>
#include <iostream>
#include <graph.h>

int main(int, char**)
{
    constexpr std::size_t size { 11 };
    
    /*for the actual graph visualization*/
    /*sample graph. See graph_sample_2_test_procedures.png*/
    constexpr std::array<edge, size> graph_sample_2 = {
        {0,2}, {0,4}, {0,5},
        {1,4},
        {2,3}, {2,4},
        {3,2}, {3,5}, {3,7}, {3,10},
        {4,5}, {4,7}, {4,9},
        {5,2}, {5,3}, {5,4},
        {6,7}, {6,8},
        {7,1}, {7,4},
        {8,4}, {8,5}, {8,10},
        {9,1}, {9,3}, {9,5},
        {10,7},{10,9}
    };
    
    graph myGraph;

    std::cout << myGraph.size() << std::endl;
    std::cout << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    myGraph = graph(GRAPH_SIZE);
    for (const auto& _edges : graph_sample_2)
        myGraph.add_edge(_edges);

    std::cout << "This line comes after insertion of few edges into graph" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "graph has (" << myGraph.size() << ") edges"<< std::endl;
    std::cout << "graph grade is: " << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    std::cout << "we print the graph" << std::endl;
    std::cout << myGraph << std::endl;

    std::cout << "path followed with dfs traversing" << std::endl; dfs_path(myGraph); std::cout << std::endl;
    std::cout << "path followed with bfs traversing" << std::endl; bfs_path(myGraph);
    
    return 0;
}
