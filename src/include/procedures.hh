#ifndef PROCEDURES_HH
#define PROCEDURES_HH

#include <iostream>
#include <graph.hh>
#include <random>
#include <stack>
#include <queue>
#include <cstdint>

/**
 * Returns true if there's a valid path from
 * start vertex to the target
 * @param gph graph to be traversed
 * @param start vertex from which we start
 * @param target the target vertex
 * @return true if there's valid path, false otherwise
*/
bool bfs(const graph& gph, vertex start, vertex target)
{
    bool found{ false };
    adjacent_t adjacents{};
    std::vector<bool> visited{};
    std::queue<vertex> next{};

    visited = std::vector<bool> (gph.grade(), false);
    next.push(start);

    visited[start] = true;
    while (next.empty() && !found)
    {
        // the vertex to be visited
        vertex vert = next.front();
        next.pop();
        adjacent_t::const_iterator next_vertex = gph.adjacents_of(vert).begin();

        // visit all neighbor vertices as long as they do not match with target vertex
        for ( ; next_vertex != adjacents.end() && !found; ++next_vertex)
        {
            if (!visited[*next_vertex])
            {
                // vertex has not been visited yet
                visited[*next_vertex] = true;

                if (!(found = *next_vertex == target))
                    next.push(*next_vertex);
            }
        }
    }

    return found;
}

/**
 * Returns true if there's a valid path from
 * start vertex to the target
 * @param gph graph to be traversed
 * @param start vertex from which we start
 * @param target the target vertex
 * @return true if there's valid path, false otherwise
*/
bool dfs(const graph& gph, vertex start, vertex target)
{
    bool found{ false };
    std::stack<vertex> next{};
    std::vector<bool> visited{ std::vector<bool> (gph.grade(), false) };

    next.push(start);
    while (!next.empty() && !found)
    {
        // next vertex to be visited
        vertex vert = next.top();
        next.pop();

        if (!visited[vert])
        {
            visited[vert] = true;
            
            if (!(found = vert == target))
            {
                for (auto adjacent : gph[vert])
                    next.push(adjacent);
            }
        }
    }

    return found;
}


/**
 * Returns the bfs traversing path for the given graph
 * @param gph graph to be traversed
 * @param vert vertex from which we start
 * @return path followed using bfs
*/
std::vector<vertex> bfs_path(const graph& gph, vertex vert)
{
    std::vector<vertex> path{ gph.grade() };
    std::queue<vertex> next{};
    std::vector<bool> visited{ std::vector<bool> (gph.grade(), false) };

    next.push(vert);

    for (std::size_t i{}; i < gph.grade(); ++i)
    {
        if (!visited[i])
        {
            visited[i] = true;
            path.insert(path.end(), i);
            while (not next.empty())
            {
                vertex front_vertex = next.front();
                next.pop();

                for (auto elem : gph[front_vertex])
                {
                    if (!visited[i])
                    {
                        path.push_back(elem);
                        visited[elem] = true;
                        next.push(elem);
                    }
                }
            }
        }
    }

    return path;
}

/**
 * Returns the dfs traversing path for the given graph
 * @param gph graph to be traversed
 * @param vert vertex from which we start
 * @return path followed using dfs
*/
void dfs_rec(const graph& gph, std::vector<bool>& vis, std::vector<vertex>& path, vertex vert)
{
    if (not vis[vert])
    {
        vis[vert] = true;
        path.insert(path.end(), vert);
        
        for (auto adjacent : gph[vert])
            dfs_rec(vert, vis, path, adjacent);
    }
}

/**
 * Returns the dfs traversing path for the given graph
 * @param gph graph to be traversed
 * @param vert vertex from which we start
 * @return path followed using dfs
*/
std::vector<vertex> dfs_path(const graph& gph, vertex p_vertex)
{
    std::vector<vertex> path{};
    std::vector<bool> visited{ std::vector<bool> (gph.grade(), false) };

    // in case we have multiple connected components
    for (std::size_t conn_comp{ p_vertex }; conn_comp < gph.grade(); ++conn_comp)
        dfs_rec(gph, visited, path, conn_comp);

    return path;
}

/**
 * Starting from a random vertex, prints to the standard output 
 * the path followed using bfs on the given graph. For each one 
 * of the vertices in prints its depth
 * @param gph graph to be traversed
*/
void bfs_path(const graph& gph)
{
    vertex vert{};
    std::queue<vertex>  next{};
    std::vector<float>  depth{ std::vector<float> (gph.grade(), - 1) };
    std::vector<bool>   visited{ std::vector<bool> (gph.grade(), false) };

    // get random vertex
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<vertex> dist6{ static_cast<std::size_t>(0), gph.grade() - 1 };
    vert = dist6(rng);


    // in case we have multiple connected components, loop through all of them
    for (std::size_t index = vert; index < gph.grade(); ++index)
    {
        if (not visited[index])
        {
            // new connected component 
            // means we start at depth 0
            depth[index] = 0;

            visited[index] = true;

            std::cout << "visiting vertex: [";
            std::cout << index << "]";
            std::cout << " : depth -> (";
            std::cout << depth[index];
            std::cout << ')' << std::endl;

            next.push(index);
            while (!next.empty())
            {
                vertex front_vertex = next.front();
                next.pop();

                for (auto adjacent : gph[front_vertex])
                {
                    if (!visited[adjacent])
                    {
                        std::cout << "visiting node: [";
                        std::cout << adjacent << "]";
                        visited[adjacent] = true;
                        depth[adjacent] = depth[front_vertex] + 1;
                        next.push(adjacent);
                        std::cout << " : depth -> (";
                        std::cout << depth[adjacent];
                        std::cout << ')' << std::endl;

                    }
                }
            }
        }
    }
}

/**
 * Starting from a random vertex, prints to the standard output 
 * the path followed using dfs on the given graph.
 * @param gph graph to be traversed
*/
void dfs_path(const graph& gph)
{
    vertex vert{};
    std::stack<vertex> next{};
    std::vector<bool> visited{ std::vector<bool> (gph.grade(), false) };

    // get random vertex
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<vertex> dist6{ static_cast<std::size_t>(0), gph.grade() - 1 };
    vert = dist6(rng);

    // loop through all connected components
    for (std::size_t node{ vert }; node < gph.grade(); ++node)
    {
        next.push(node);
        while (not next.empty())
        {
            vertex temp = next.top();
            next.pop();
            
            if (!visited[temp])
            {
                visited[temp] = true;
                std::cout << "visiting node: [";
                std::cout << temp << ']' << std::endl;
                for (auto adjacent : gph[temp])
                    next.push(adjacent);
            }
        }
    }
}

#endif // END PROCEDURES_HH
