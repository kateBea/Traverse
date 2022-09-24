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
    if (argc != 2)
    {
        usage();
        return 0;
    }


    std::size_t size {};
    std::vector<edge> graph_sample{};
    if (not file_setup(argv[1], graph_sample, size))
        return 1;

    graph myGraph(size);
    for (const auto& l_edges : graph_sample)
        myGraph.add_edge(l_edges);

    std::cout << "graph size: " << myGraph.size() << std::endl;
    std::cout << "graph degree: " << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;


    std::cout << "\nAfter adding few edges into the graph" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    std::cout << "print the graph" << std::endl;
    std::cout << myGraph << std::endl;

    std::cout << "path followed with dfs" << std::endl;
    dfs_path(myGraph);
    std::cout << std::endl;

    std::cout << "path followed with bfs" << std::endl;
    bfs_path(myGraph);

    return 0;
}
