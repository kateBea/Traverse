/**
 * @file main.cc
 * @brief
 * @version 1.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 */

#include <cstdint>
#include <vector>
#include <iostream>
#include <cstdlib>

#include <graph.h>
#include <procedures.h>
#include <setup.h>

void usage()
{
    std::cerr << "usage: traverse file_name grap_degree\n"
    "Program expects three arguments\n";
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        usage();
        return 0;
    }

    const auto size { 11 };

    /*for the actual graph visualization*/
    /*sample graph. See graph_sample_2_test_procedures.png*/

    std::vector<edge> graph_sample{};
    if (not file_setup(argv[1], graph_sample))
        return 1;
    else
        std::cerr << "could read file. Vector size is: " << graph_sample.size()<< std::endl;

    graph myGraph(size);

    std::cout << myGraph.size() << std::endl;
    std::cout << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty: " << graph_sample.size() << std::endl;
    else                    std::cout << "graph is not empty" << graph_sample.size() << std::endl;

    for (const auto& _edges : graph_sample)
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
