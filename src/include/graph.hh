#ifndef GRAPH_HH
#define GRAPH_HH

#include <utility>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>
#include <list>
#include <set>

using vertex        = std::size_t;
using edge          = std::pair<vertex, vertex>;
using adjacent_t    = std::vector<vertex>;
using graph_t       = std::vector<adjacent_t>;
using edge_set_t    = std::set<edge>;

class graph
{
public:
    /**
     * Initializes this graph with n vertices
     * @param n total amount of vertices
     * 
    */
    graph(std::size_t n = 0) 
        :   m_graph (graph_t (n, adjacent_t ()))
    {   }

    /**
     * Returns the total count of edges
     * @return Total count of edges
    */
   [[nodiscard]]
    std::size_t size() const { return m_edges.size(); }

    /**
     * Returns the total count of vertices
     * @return Total count of vertices
    */
   [[nodiscard]]
    std::size_t grade() const { return m_graph.size(); }

    /**
     * Adds the edge passes as parameter to the graph.
     * If it already existed this function has no effects
     * @param edge the edge to be added
     * 
    */
    void add_edge(const edge& edg)
    {
        if (m_edges.find(edg) == m_edges.end())
        {
            //check if _edge contains valid edge values
            bool range_1 =  edg.second <= m_graph.size() - 1;
            bool range_2 =  edg.first <= m_graph.size() - 1;
            bool ribbon  =  edg.first == edg.second;

            assert((range_1 or range_2) && !ribbon );

            m_edges.insert(edg);

            // add directed edge that goes from edg.first to edg.second
            m_graph[edg.first].push_back(edg.second);
        }
    }

    /**
     * Add a new vertex to the graph
    */
    void add_vertex() { m_graph.push_back(adjacent_t ()); }

    /* returns true if the graph is empty, meaning it contains
    no edges but may contain nodes, false if it contains at least one edge*/

    /**
     * Returns true if the graph is empty, meaning it contains 
     * no edges but may contain nodes, false otherwise
     * @return true if graph has no nodes, false otherwise
    */
    [[nodiscard]]
    bool empty() const { return m_edges.size() == 0; }

    /* erase edge _edge from the set of edges of the graph*/

    /**
     * Erase the edge passed as parameter from the graph
     * @param edg edge to be erased from this graph
    */
    void delete_edge(const edge& edg)
    {
        if (m_edges.find(edg) == m_edges.end())
        {
            // check if edg contains valid edge values
            bool range_1 = edg.second <= m_graph.size() - 1;
            bool range_2 = edg.first <= m_graph.size() - 1;
            assert(range_1 or range_2);

            // erase from the set of edges
            m_edges.erase(edg);

            // erase edg.second from the list of adjacent_t vertex of edg.first
            auto is_adjacent_t = [&edg](vertex v) { return v == edg.second; };
            auto adjacen_first = m_graph[edg.first].begin();
            auto adjacen_last = m_graph[edg.first].end();
            auto it = std::find_if(adjacen_first, adjacen_last, is_adjacent_t);
            m_graph[edg.first].erase(it);
        }
    }

    /* erase last vertex from the graph*/

    /**
     * Erase the last vertex from the graph
    */
    void vertex_pop()
    {
        vertex last = m_graph.size() - 1;

        // first we remove all the edges incidents to last
        // from the set of edges
        auto elem = m_edges.begin();
        for ( ; elem != m_edges.end(); ++elem)
        {
            // we erase all edges the last vertex is part of
            if (elem->first == last || elem->second == last)
                elem = m_edges.erase(elem);
        } 

        // after the cleanup we erase the last vertex
        m_graph.pop_back();
    }

    /**
     * Returns the density of the graph
     * @return density of this graph
    */
    [[nodiscard]]
    float density() const
    {
        float size = this->size();
        float grade = this->grade();
        float vertices_count = (size * (size - 1.0f)) / 2.0f;

        return 2.0f * size / vertices_count;
    }

    /**
     * Returns the numbers of edges which the given vertex
     * is an endpoint of
     * 
    */
    [[nodiscard]]
    std::size_t degree(vertex vert) const
    {
        assert(vert < m_graph.size() && "vertex is not a valid vertex");
        return m_graph[vert].size();
    }

    /**
     * Returns the numbers of edges which the given vertex
     * is an endpoint of 
     * @return adjacents of vert
    */
    [[nodiscard]]
    std::vector<vertex>& adjacents_of(vertex vert)
    {
        assert(vert < m_graph.size());

        return m_graph[vert];
    }

    /**
     * Returns the numbers of edges which the given vertex
     * is an endpoint of 
     * @return adjacents of vert
    */
    [[nodiscard]]
    std::vector<vertex>& operator[](vertex vert)
    {
        return adjacents_of(vert);
    }

    /**
     * Returns the numbers of edges which the given vertex
     * is an endpoint of 
     * @return adjacents of vert
    */
    [[nodiscard]]
    const std::vector<vertex>& adjacents_of(vertex vert) const
    {
        assert(vert < m_graph.size());

        return m_graph[vert];
    }

    /**
     * Returns the numbers of edges which the given vertex
     * is an endpoint of 
     * @return adjacents of vert
    */
    [[nodiscard]]
    const std::vector<vertex>& operator[](vertex vert) const
    {
        return adjacents_of(vert);
    }

    /**
     * Prints every vertex with all of its adjacent_ts in
     * an adjacency list format
    */
    friend std::ostream& operator<<(std::ostream& out, const graph& graph)
    {
        for (std::size_t index = 0; index < graph.grade(); ++index)
        {
            out << "adjacent_ts of vertex: (" << index << "): ";
            for (auto vert : graph[index])
                out << '[' << vert << "] ";

            out << '\n';
        }

        return out;
    }

private:
    // graph container
    graph_t m_graph{};

    // set of all edges from the graph
    edge_set_t m_edges{};
};

#endif //END GRAPH_HH
