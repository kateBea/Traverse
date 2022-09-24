#ifndef PROCEDURES_HH
#define PROCEDURES_HH

#include <iostream>
#include <graph.h>
#include <random>
#include <stack>
#include <queue>
#include <cstdint>

/* true if theres path from frist vertex to second */
bool bfs_to_target(const graph& p_graph, vertex start, vertex target)
{
    std::size_t total_vertices{};
    bool target_found{ false };
    std::list<vertex> adjacents{};
    std::vector<bool> visited_nodes{};
    std::queue<vertex> next_on_line{};

    total_vertices = p_graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);
    next_on_line.push(start);

    visited_nodes[start] = true;
    while (not next_on_line.empty())
    {
        vertex front_vertex = next_on_line.front();
        next_on_line.pop();
        adjacents = p_graph.m_graph[front_vertex];
        std::list<vertex>::iterator next_vertex = adjacents.begin();

        // visit all neighbor vertices as long as they do not match with target vertex
        for ( ; next_vertex != adjacents.end() and not target_found; ++next_vertex)
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

/* true if theres path from frist vertex to second */
bool dfs_to_target(const graph& p_graph, vertex start, vertex target)
{
    bool target_found{ false };
    std::stack<vertex> next_on_line{};
    std::size_t total_vertices{ p_graph.grade() };
    std::vector<bool> visited_nodes{ std::vector<bool> (total_vertices, false) };

    next_on_line.push(start);
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
                for (auto adjacent : p_graph.m_graph[next_vertex])
                    next_on_line.push(adjacent);
            }
        }
        
        if (target_found)
            break;
    }

    return target_found;
}

/* bfs path starting from given vertex */
std::list<vertex> bfs_path(const graph& p_graph, vertex p_vertex)
{
    std::list<vertex> path{};
    std::queue<vertex> next_on_line{};
    std::size_t total_vertices{ p_graph.grade() };
    std::vector<bool> visited_nodes{ std::vector<bool> (total_vertices, false) };

    next_on_line.push(p_vertex);

    for (std::size_t i{}; i < total_vertices; ++i)
    {
        if (not visited_nodes[i])
        {
            visited_nodes[i] = true;
            path.insert(path.end(), i);
            while (not next_on_line.empty())
            {
                vertex front_vertex = next_on_line.front();
                next_on_line.pop();

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

/* immersion dfs_path */
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

/* dfs path starting from given vertex */
std::list<vertex> dfs_path(const graph& p_graph, vertex p_vertex)
{
    std::list<vertex> path{};
    std::size_t total_vertices{ p_graph.grade() };
    std::vector<bool> visited_vertices{ std::vector<bool> (total_vertices, false) };

    for (std::size_t conn_comp{ p_vertex }; conn_comp < total_vertices; ++conn_comp)
        dfs_rec(p_graph, visited_vertices, path, conn_comp);

    return path;
}

/* bfs path all connected component*/
/* start traversing from random vertex*/
/* print visited nodes to standard error channel*/
/* print depth distance of every visited vertex*/
void bfs_path(const graph& p_graph)
{
    vertex l_vertex{};
    std::queue<vertex>  next_on_line{};
    std::size_t total_vertices{ p_graph.grade() };
    std::vector<float>  depth{ std::vector<float> (total_vertices, - 1) };
    std::vector<bool>   visited_nodes{ std::vector<bool> (total_vertices, false) };

    std::mt19937        rng{ std::random_device() };

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
            std::cout << " : depth -> (";
            std::cout << depth[node];
            std::cout << ')' << std::endl;

            next_on_line.push(node);
            while (not next_on_line.empty())
            {
                vertex front_vertex = next_on_line.front();
                next_on_line.pop();

                for (auto adjacent : p_graph.m_graph[front_vertex])
                {
                    if (not visited_nodes[adjacent])
                    {
                        std::cout << "visiting node: [";
                        std::cout << adjacent << "]";
                        visited_nodes[adjacent] = true;
                        depth[adjacent] = depth[front_vertex] + 1;
                        next_on_line.push(adjacent);
                        std::cout << " : depth -> (";
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
    vertex l_vertex{};
    std::stack<vertex>  next_on_line{};
    std::size_t total_vertices{ p_graph.grade() };
    std::vector<bool>   visited_nodes{ std::vector<bool> (total_vertices, false) };

    std::mt19937            rng{ std::random_device() };

    // distribution in range [0, total_vertices)
    std::uniform_int_distribution<std::size_t> dist6{ static_cast<std::size_t>(0), total_vertices - 1 };
    l_vertex             =   static_cast<vertex>(dist6(rng));

    // loop through all connected components
    for (std::size_t node{ l_vertex }; node < total_vertices; ++node)
    {
        next_on_line.push(node);
        while (not next_on_line.empty())
        {
            vertex temp = next_on_line.top();
            next_on_line.pop();
            
            if (not visited_nodes[temp])
            {
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
