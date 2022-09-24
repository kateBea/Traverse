#ifndef PROCEDURES_HH
#define PRORCEDURES_HH

#include <iostream>
#include <graph.h>
#include <random>
#include <stack>
#include <queue>
#include <cstdint>

/* true if theres path from frist vertex to second (implements bfs)*/
bool bfs_to_target(const graph& p_graph, vertex start, vertex target)
{
    std::size_t total_vertices;
    bool target_found;
    std::list<vertex> adjacents;
    std::vector<bool> visited_nodes;
    std::queue<vertex> next_on_line;

    total_vertices = p_graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);
    next_on_line.push(start);

    target_found = false;
    visited_nodes[start] = true;
    while (not next_on_line.empty())
    {
        vertex front_vertex = next_on_line.front();
        next_on_line.pop();
        adjacents = p_graph.m_graph[front_vertex];
        std::list<vertex>::iterator next_vertex = adjacents.begin();

        // visit all neighbor vertices as long as they do not match with target vertex
        for (; next_vertex != adjacents.end() and not target_found; ++next_vertex)
        {
            if (not visited_nodes[*next_vertex])
            {
                // vertex has not been visited yet
                visited_nodes[*next_vertex] = true;
                target_found = *next_vertex == target;

                if (not target_found)
                    next_on_line.push(*next_vertex);
            }
        }

        if (target_found)
            break;
    }

    return target_found;
}

/* true if theres path from frist vertex to second (implements dfs)*/
bool dfs_to_target(const graph& p_graph, vertex start, vertex target)
{
    std::size_t total_vertices;
    bool target_found;
    std::vector<bool> visited_nodes;
    std::stack<vertex> next_on_line;

    total_vertices = p_graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);

    next_on_line.push(start);
    target_found = false;
    while (not next_on_line.empty())
    {
        vertex next_vertex = next_on_line.top();
        next_on_line.pop();

        if (not visited_nodes[next_vertex])
        {
            visited_nodes[next_vertex] = true;
            target_found = next_vertex == target;
            if (not target_found)
            {
                // if target not found explore adjacent vertices
                for (auto adjacent : p_graph.m_graph[next_vertex])
                    next_on_line.push(adjacent);
            }
        }

        // stop traversing graph if target found
        if (target_found)
            break;
    }

    return target_found;
}

/* bfs path starting from given vertex*/
std::list<vertex> bfs_path(const graph& p_graph, vertex p_vertex)
{
    std::size_t total_vertices;
    std::vector<bool> visited_nodes;
    std::queue<vertex> next_on_line;
    std::list<vertex> path;

    total_vertices = p_graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);
    next_on_line.push(p_vertex);

    // visit all connected components
    for (std::size_t i = 0; i < total_vertices; ++i)
    {
        if (not visited_nodes[i])
        {
            /*vertex has not been visited yet*/
            visited_nodes[i] = true;
            path.insert(path.end(), i);
            while (not next_on_line.empty())
            {
                vertex front_vertex = next_on_line.front();
                next_on_line.pop();

                /*visit all neighbor vertices*/
                for (auto next_vertex : p_graph.m_graph[front_vertex])
                {
                    if (not visited_nodes[i])
                    {
                        path.insert(path.end(), next_vertex);
                        visited_nodes[next_vertex] = true;
                        next_on_line.push(next_vertex);
                    }
                }
            }
        }
    }

    return path;
}

/* immersion dfs_path*/
void dfs_rec(const graph& p_graph, std::vector<bool>& vis, std::list<vertex>& path, vertex p_vertex)
{
    if (not vis[p_vertex])
    {
        vis[p_vertex] = true;
        path.insert(path.end(), p_vertex);
        for (auto adjacent : p_graph.m_graph[p_vertex])
            dfs_rec(p_graph, vis, path, adjacent);
    }
}

/* dfs path starting from given vertex*/
std::list<vertex> dfs_path(const graph& p_graph, vertex p_vertex)
{
    std::size_t total_vertices;
    std::vector<bool> visited_vertices;
    std::list<vertex> path;

    total_vertices = p_graph.grade();
    visited_vertices = std::vector<bool> (total_vertices, false);

    // loop through connected components starting from _vertex in incresing order
    for (std::size_t conn_comp = p_vertex; conn_comp < total_vertices; ++conn_comp)
        dfs_rec(p_graph, visited_vertices, path, conn_comp);

    return path;
}

/* bfs path all connected component*/
/* start traversing from random vertex*/
/* print visited nodes to standard error channel*/
/* print depth distance of every visited vertex*/
void bfs_path(const graph& p_graph)
{
    std::size_t total_vertices;
    vertex l_vertex{};
    std::vector<bool>   visited_nodes{};
    std::vector<float>  depth{};
    std::queue<vertex>  next_on_line{};

    total_vertices  =   p_graph.grade();
    visited_nodes   =   std::vector<bool> (total_vertices, false);
    depth           =   std::vector<float> (total_vertices, - 1);

    std::random_device  dev{};
    std::mt19937        rng{ dev() };

    // distribution in range [0, total_vertices)
    std::uniform_int_distribution<std::size_t> dist6{ static_cast<std::size_t>(0), total_vertices - 1 };
    l_vertex         =   static_cast<vertex>(dist6(rng));


    // in case we have separedted connected components loop through all of them
    for (std::size_t node = l_vertex; node < total_vertices; ++node)
    {
        if (not visited_nodes[node])
        {
            // new connected component mean we start at depth 0
            depth[node] = 0;

            visited_nodes[node] = true;
            std::cout << "visiting node: [";
            std::cout << node << "]";
            std::cout << " : deph -> (";
            std::cout << depth[node];
            std::cout << ')' << std::endl;

            next_on_line.push(node);
            while (not next_on_line.empty())
            {
                vertex front_vertex = next_on_line.front();
                next_on_line.pop();

                // visit all neighbor vertices
                for (auto adjacent : p_graph.m_graph[front_vertex])
                {
                    if (not visited_nodes[adjacent])
                    {
                        std::cout << "visiting node: [";
                        std::cout << adjacent << "]";
                        visited_nodes[adjacent] = true;
                        depth[adjacent] = depth[front_vertex] + 1;
                        next_on_line.push(adjacent);
                        std::cout << " : deph -> (";
                        std::cout << depth[adjacent];
                        std::cout << ')' << std::endl;

                    }
                }
            }
        }
    }
}

/* dfs path all connected component*/
/* start traversing from random vertex*/
/* print visited nodes to standard error channel*/
void dfs_path(const graph& p_graph)
{
    size_t total_vertices;
    vertex l_vertex;
    std::stack<vertex>  next_on_line;
    std::vector<bool>   visited_nodes;

    total_vertices      =   p_graph.grade();
    visited_nodes       =   std::vector<bool> (total_vertices, false);

    // pick random vertex*/
    std::random_device      dev{};
    std::mt19937            rng{ dev() };

    // distribution in range [0, total_vertices)
    std::uniform_int_distribution<std::size_t> dist6{ static_cast<std::size_t>(0), total_vertices - 1 };
    l_vertex             =   static_cast<vertex>(dist6(rng));

    // loop through all connected components
    for (std::size_t node = l_vertex; node < total_vertices; ++node)
    {
        next_on_line.push(node);
        while (not next_on_line.empty())
        {
            vertex temp = next_on_line.top();
            next_on_line.pop();
            if (not visited_nodes[temp])
            {
                // neighbors has not been visited yet
                visited_nodes[temp] = true;
                std::cout << "visiting node: [";
                std::cout << temp << "]" << std::endl;
                for (auto adjacent : p_graph.m_graph[temp])
                    next_on_line.push(adjacent);
            }
        }
    }
}

#endif // END PROCEDURES_HH
