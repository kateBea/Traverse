#ifndef SETUP_HH
#define SETUP_HH

#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <string_view>

#include <graph.h>

bool file_setup(std::string_view    file_name,
                std::vector<edge>&  graph,
                std::size_t         &degree)
{
    std::ifstream nodes_input{ file_name.data() };
    std::stringstream file_stream{};

    file_stream << nodes_input.rdbuf();

    if (!nodes_input)
    {
        std::cerr << "Could not open '" << file_name << "' file\n";
        return false;
    }

    edge temp_edge;
    bool first{ true };

    while (!file_stream.eof())
    {
        if (first)
        {
            file_stream >> degree;
            first = false;
        }
        else
        {
            file_stream >> temp_edge.first;
            file_stream >> temp_edge.second;

            graph.push_back(temp_edge);
        }
    }

    return true;
}

#endif // END GRAPH_HH
