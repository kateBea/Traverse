#ifndef GRAPH_HH
#define GRAPH_HH

#include <utility>
#include <vector>
#include <cassert>
#include <list>
#include <set>

typedef std::pair<int, int> edge;
typedef int vertex;

//DEFINITION OF CLASS GRAPH
class graph
{
public:
    /*default constructor*/
    graph() {}

    /*parametrized constructor. Graph with n vertices*/
    graph(int n) :
        _graph (std::vector<std::list<vertex>> (n, std::list<vertex>())) {}
    
    /*total amount of edges*/
    unsigned int size() {return edges.size();}

    /*total amount of vertices*/
    unsigned int grade() {return _graph.size();}

    /*add edge to graph. No changes if elready existed*/
    void add_edge(const edge& _edge)
    {
        std::set<edge>::const_iterator it = edges.find(_edge);
        if (it == edges.end())
        {   
            //check if _edge contains valid edge values
            bool range_1 = _edge.first >= 0 and _edge.second <= _graph.size() -1;
            bool range_2 = _edge.second >= 0 and _edge.first <= _graph.size() -1;
            assert(range_1 or range_2);

            edges.insert(_edge);
            _graph[_edge.first].push_back(_edge.second);
        }
    }

    /*simply increment the amount of vertex graph can hold*/
    void vertex_push() {_graph.push_back(std::list<vertex> ());}
    void delete_edge(const edge& _edge)
    {
        std::set<edge>::const_iterator it = edges.find(_edge);
        if (it == edges.end())
        {   
            //check if _edge contains valid edge values
            bool range_1 = _edge.first >= 0 and _edge.second <= _graph.size() -1;
            bool range_2 = _edge.second >= 0 and _edge.first <= _graph.size() -1;
            assert(range_1 or range_2);

            //era edge from graph
            edges.erase(_edge);
            auto it1 = _graph[_edge.first].begin();
            bool found = false;
            while (it1 != _graph[_edge.first].end() and not found) 
            {
                if (*it1 == _edge.second) found = true;
                else ++it1;
            }
            _graph[_edge.first].erase(it1);
        }
    }

    /*erase last vertex from the graph*/
    void vertex_pop()
    {
        vertex _vertex = _graph.size()-1;

        //first we remove all the edges incidents to _vertex
        for (vertex vt : _graph[_vertex])
        {
            edge target = std::make_pair(_vertex, vt);
            auto it = edges.find(target);
            if (it != edges.end()) edges.erase(it);
        }

        //after the cleanup we erase 
        _graph.pop_back();
    }

    /*return the graph density*/
    float graph_density() 
    {
        float size = edges.size();
        float total_vertices = _graph.size();
        float all_vertices = (total_vertices * (total_vertices - 1)) /2;
        
        return 2*size / all_vertices; 
    }

    /*returns the number of edges incidents to the vertex*/
    unsigned int vertex_degree(const vertex& _vertex)
    {
        assert(_vertex >= 0 and _vertex < _graph.size());
        //vertex is valid
        
        //to be revised still
        return _graph[_vertex].size();
    }

    /*returns a reference to a list of all the vertices adjacent to _vertex*/
    std::list<vertex>& adjacents_of_vertex(vertex _vertex)
    {
        assert(_vertex >= 0 and _vertex < _graph.size());
        //vertex is valid

        return _graph[_vertex];
    }

    /*operator overload that works similar to adjacents_of_vertex*/
    std::list<vertex>& operator[](const vertex& _vertex)
    {
        return adjacents_of_vertex(_vertex);
    }

private:
    //graph container
    std::vector<std::list<vertex>> _graph;

    //all the edges in the graph
    std::set<edge> edges;
};

#endif //END GRAPH_HH