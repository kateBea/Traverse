
// C++ Standard Library
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstddef>
#include <vector>
#include <sstream>
#include <iterator>
#include <string_view>

// Project Library
#include <graph.hh>
#include <procedures.hh>

// returns -1 if the are no edges in the file
// or the file could not be opened
std::int32_t read_edges(std::string_view name, std::vector<edge>& edges)
{
    std::int32_t nodes{ -2 };
    std::ifstream file{ name.data() };

    if (!file)
    {
        std::cerr << "Could not open '" << name << "' file\n";
        return nodes + 1;
    }

    edge edg;

    while (!file.eof())
    {
        file >> edg.first;
        file >> edg.second;

        nodes = std::max(std::max<decltype(nodes)>(edg.first, edg.second), nodes);

        edges.push_back(edg);
    }

    return nodes + 1;
}

void usage()
{
    std::cerr << "usage: traverse file\n"
                 "Program expects three arguments\n";
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage();
        return 0;
    }


    std::vector<edge> edges{};
    auto nodes_count = read_edges(argv[1], edges);
    if (nodes_count == -1)
        return 1;

    graph gph(nodes_count);

    std::cout << "graph size: " << gph.size() << '\n';
    std::cout << "graph degree: " << gph.grade() << '\n';

    std::cout << "\nAdding edges to the graph" << '\n';
    std::cout << "-------------------------------------------------------" << '\n';

    for (const auto& edg : edges)
        gph.add_edge(edg);

    if (gph.empty())    
        std::cout << "graph is empty" << '\n';
    else
        std::cout << "graph is not empty" << '\n';

    std::cout << "print the graph" << '\n';
    std::cout << gph << '\n';

    std::cout << "path followed with dfs" << '\n';
    dfs_path(gph);

    std::cout << '\n';

    std::cout << "path followed with bfs" << '\n';
    bfs_path(gph);

    return 0;
}
