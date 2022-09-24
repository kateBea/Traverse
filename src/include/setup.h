#ifndef SETUP_HH
#define SETUP_HH

#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <string_view>

#include <graph.h>

bool file_setup(std::string_view file_name, std::vector<edge>& graph)
{
    std::cout << "file name: " << file_name.data() << std::endl;
    std::ifstream nodes_input{ file_name.data() };
    std::stringstream file_stream{};

    file_stream << nodes_input.rdbuf();

    if (!nodes_input)
    {
        std::cerr << "Could not open " << file_name << " file\n";
        return false;
    }

    edge temp_edge;
    std::vector<edge> graph_sample{};

    while (!file_stream.eof())
    {
        file_stream >> temp_edge.first;
        file_stream >> temp_edge.second;

        graph.push_back(temp_edge);
    }

    for (std::size_t index{}; index < graph_sample.size(); ++index)
    {
        std::cout << graph_sample[index].first << ' ';
        std::cout << graph_sample[index].second << std::endl;
    }

    return true;
}

#endif // END GRAPH_HH
