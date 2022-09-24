#ifndef GRAPH_HH
#define GRAPH_HH

#include <utility>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>
#include <list>
#include <set>

using vertex    = std::size_t;
using edge      = std::pair<vertex, vertex>;

class graph
{
public:
    /* parametrized constructor. Graph with n vertices*/
    graph(std::size_t n = 0) :
        m_graph (std::vector<std::list<vertex>> (n, std::list<vertex>()))
    {   }

    /* total amount of edges*/
    std::size_t size() const { return m_edges.size(); }

    /* total amount of vertices*/
    std::size_t grade() const { return m_graph.size(); }

    /* add edge to graph. No changes if elready existed*/
    void add_edge(const edge& p_edge)
    {
        std::set<edge>::const_iterator it = m_edges.find(p_edge);
        if (it == m_edges.end())
        {
            //check if _edge contains valid edge values
            bool range_1 =  p_edge.second <= m_graph.size() - 1;
            bool range_2 =  p_edge.first <= m_graph.size() - 1;
            bool ribbon  =  p_edge.first == p_edge.second;

            assert((range_1 or range_2) and not ribbon);

            m_edges.insert(p_edge);
            m_graph[p_edge.first].push_back(p_edge.second);
        }
    }

    /* increment the amount of vertex graph can hold*/
    void vertex_push() { m_graph.push_back(std::list<vertex> ()); }

    /* returns true if the graph is empty, meaning it contains
    no edges but may contain nodes, false if it contains at least one edge*/
    bool empty() const { return m_edges.size() == 0; }

    /* erase edge _edge from the set of edges of the graph*/
    void delete_edge(const edge& p_edge)
    {
        std::set<edge>::const_iterator it = m_edges.find(p_edge);
        if (it == m_edges.end())
        {
            // check if edge contains valid edge values
            bool range_1 = p_edge.second <= m_graph.size() - 1;
            bool range_2 = p_edge.first <= m_graph.size() - 1;
            assert(range_1 or range_2);

            m_edges.erase(p_edge);
            auto it1 = m_graph[p_edge.first].begin();
            bool found = false;

            while (it1 != m_graph[p_edge.first].end() and not found)
            {
                if (*it1 == p_edge.second)
                    found = true;
                else
                    ++it1;
            }
            m_graph[p_edge.first].erase(it1);
        }
    }

    /* erase last vertex from the graph*/
    void vertex_pop()
    {
        vertex l_vertex = m_graph.size() - 1;

        // first we remove all the edges incidents to _vertex
        for (vertex vt : m_graph[l_vertex])
        {
            edge target = std::make_pair(l_vertex, vt);
            auto it = m_edges.find(target);
            if (it != m_edges.end())
                m_edges.erase(it);
        }

        // after the cleanup we erase
        m_graph.pop_back();
    }

    /* return the graph density*/
    float graph_density() const
    {
        float size = static_cast<float>(m_edges.size());
        float total_vertices = static_cast<float>(m_graph.size());
        float all_vertices = (total_vertices * (total_vertices - 1.0f)) / 2.0f;

        return 2.0f * size / all_vertices;
    }

    /* returns the number of edges incidents to the vertex*/
    std::size_t vertex_degree(vertex p_vertex) const
    {
        assert(p_vertex < m_graph.size());

        return m_graph[p_vertex].size();
    }

    /* returns a reference to a list of all the vertices adjacent to _vertex*/
    std::list<vertex>& adjacents_of_vertex(vertex p_vertex)
    {
        assert(p_vertex < m_graph.size());

        return m_graph[p_vertex];
    }

    /* operator overload that works similar to adjacents_of_vertex*/
    std::list<vertex>& operator[](vertex p_vertex)
    {
        return adjacents_of_vertex(p_vertex);
    }

    /* print the whole adjacency list of a graph to the std error channel*/
    /* every vertex with its adjacents*/
    friend std::ostream& operator<<(std::ostream& out, const graph& graph)
    {
        for (unsigned int i = 0; i < graph.grade(); ++i)
        {
            out << "adjacents of vertex: (" << i << "): ";
            for (auto l_vertex : graph.m_graph[i])
                out << "[" << l_vertex << "] ";

            out << std::endl;
        }

        return out;
    }

    // graph container
    std::vector<std::list<vertex>> m_graph;

    // complete set of edges from the graph
    std::set<edge> m_edges;
};

#endif //END GRAPH_HH
