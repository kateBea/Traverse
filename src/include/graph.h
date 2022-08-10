/**
 * @file graph.h
 * @brief 
 * @version 1.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <iostream>
#include <vector>
#include <cassert>
#include <list>
#include <set>

#ifdef WINDOWS_ISSUE
// I got an error when building on windwos 
// for usage of and, not, or keywords
// these macros fixed it, pretty scuffed fix
#define not !
#define and &&
#define or  ||
#endif

typedef     size_t                      vertex;
typedef     std::pair<vertex, vertex>   edge;

//DEFINITION OF CLASS GRAPH
struct graph
{
    /*default constructor*/
    graph() {}

    /*parametrized constructor. Graph with n vertices*/
    graph(int n) :
        _graph (std::vector<std::list<vertex>> (n, std::list<vertex>())) {}
    
    /*total amount of edges*/
    size_t size() const {return edges.size();}

    /*total amount of vertices*/
    size_t grade() const {return _graph.size();}

    /*add edge to graph. No changes if elready existed*/
    void add_edge(const edge& _edge)
    {
        std::set<edge>::const_iterator it = edges.find(_edge);
        if (it == edges.end())
        {   
            //check if _edge contains valid edge values
            bool range_1 =  _edge.second <= _graph.size() -1;
            bool range_2 =  _edge.first <= _graph.size() -1;
            bool ribbon  =  _edge.first == _edge.second;     

            assert((range_1 or range_2) and not ribbon);

            edges.insert(_edge);
            _graph[_edge.first].push_back(_edge.second);
        }
    }

    /*increment the amount of vertex graph can hold*/
    void vertex_push() {_graph.push_back(std::list<vertex> ());}

    /*Returns true if the graph is empty, false otherwise*/
    bool empty() const {return _graph.size() == 0;}

    /*erase edge _edge from the set of edges of the graph*/
    void delete_edge(const edge& _edge)
    {
        std::set<edge>::const_iterator it = edges.find(_edge);
        if (it == edges.end())
        {   
            //check if _edge contains valid edge values
            bool range_1 = _edge.second <= _graph.size() -1;
            bool range_2 = _edge.first <= _graph.size() -1;
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
    float graph_density() const
    {
        float size = edges.size();
        float total_vertices = _graph.size();
        float all_vertices = (total_vertices * (total_vertices - 1)) /2;
        
        return 2*size / all_vertices; 
    }

    /*returns the number of edges incidents to the vertex*/
    size_t vertex_degree(const vertex& _vertex) const
    {
        assert(_vertex < _graph.size());
        //vertex is valid
        
        //to be revised still
        return _graph[_vertex].size();
    }

    /*returns a reference to a list of all the vertices adjacent to _vertex*/
    std::list<vertex>& adjacents_of_vertex(vertex _vertex)
    {
        assert(_vertex < _graph.size());
        //vertex is valid

        return _graph[_vertex];
    }

    /*operator overload that works similar to adjacents_of_vertex*/
    std::list<vertex>& operator[](const vertex& _vertex)
    {
        return adjacents_of_vertex(_vertex);
    }

    /*Print the whole adjacency list of a graph to the std error channel*/ 
    /*Every vertex with its adjacents*/
    friend std::ostream& operator<<(std::ostream& _cout, const graph& _graph)
    {
        for (unsigned int i = 0; i < _graph.grade(); ++i)
        {
            std::cerr << "adjacents of vertex: (" << i << "): ";
            for (const auto _vertex : _graph._graph[i])
                std::cerr << "[" << _vertex << "] ";
            std::cerr << std::endl;
        }
        return _cout;
    }

    
    //graph container
    std::vector<std::list<vertex>> _graph;

    //all the edges in the graph
    std::set<edge> edges;
};

#endif //END GRAPH_HH
