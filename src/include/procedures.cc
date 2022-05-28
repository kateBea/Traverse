/**
 * @file procedures.cc
 * @author kate (zanetty54@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <procedures.h>
#include <iostream>
#include <random>
#include <stack>
#include <queue>

/*true if theres path from frist vertex to second (implements bfs)*/
bool bfs_to_target(const graph& _graph, vertex start, vertex target)
{   
    int total_vertices;
    bool target_found;
    std::list<vertex> adjacents;
    std::vector<bool> visited_nodes;
    std::queue<vertex> next_on_line;

    total_vertices = _graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);
    next_on_line.push(start);

    target_found = false;
    visited_nodes[start] = true;
    while (not next_on_line.empty())
    {
        vertex front_vertex = next_on_line.front();
        next_on_line.pop();
        adjacents = _graph._graph[front_vertex];
        std::list<vertex>::iterator next_vertex = adjacents.begin();

        /*visit all neighbor vertices as long as they do not match with target vertex*/
        for (; next_vertex != adjacents.end() and not target_found; ++next_vertex)
        {
            if (not visited_nodes[*next_vertex])
            {
                /*vertex has not been visited yet*/
                visited_nodes[*next_vertex] = true;
                target_found = *next_vertex == target;
                if (not target_found) next_on_line.push(*next_vertex);
            }
        }

        if (target_found) break;
    }

    return target_found;
}

/*true if theres path from frist vertex to second (implements dfs)*/
bool dfs_to_target(const graph& _graph, vertex start, vertex target)
{
    int total_vertices;
    bool target_found;
    std::vector<bool> visited_nodes;
    std::stack<vertex> next_on_line;

    total_vertices = _graph.grade();
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
                /*if target not found explore adjacent vertices*/
                for (auto adjacent : _graph._graph[next_vertex])
                    next_on_line.push(adjacent);    
            }
        }

        /*stop traversing graph if target found*/
        if (target_found) break;
    }
}

/*bfs path starting from given vertex*/
std::list<vertex> bfs_path(const graph& _graph, vertex _vertex)
{
    int total_vertices;
    std::vector<bool> visited_nodes;
    std::queue<vertex> next_on_line;
    std::list<vertex> path;

    total_vertices = _graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);
    next_on_line.push(_vertex);

    /*visit all connected components*/
    for (int i = 0; i < total_vertices; ++i)
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
                for (auto next_vertex : _graph._graph[front_vertex])
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

/*immersion dfc_path*/
void dfs_rec(const graph& _graph, std::vector<bool>& vis, std::list<vertex>& path, vertex _vertex)
{
    if (not vis[_vertex])
    {
        vis[_vertex] = true;
        path.insert(path.end(), _vertex);
        for (auto adjacent : _graph._graph[_vertex]) 
            dfs_rec(_graph, vis, path, adjacent);
    }
}

/*dfs path starting from given vertex*/
std::list<vertex> dfs_path(const graph& _graph, vertex _vertex)
{   
    int total_vertices;
    std::vector<bool> visited_vertices;
    std::list<vertex> path;

    total_vertices = _graph.grade();
    visited_vertices = std::vector<bool> (total_vertices, false);

    /*loop through all connected components*/
    for (int conn_comp = 0; conn_comp < total_vertices; ++conn_comp)
        dfs_rec(_graph, visited_vertices, path, conn_comp);

    return path;
}

/*bfs path all connected component*/
/*start traversing from random vertex*/
/*Print visited nodes to standard error channel*/
void bfs_path(const graph& _graph)
{
    int total_vertices;
    vertex _vertex;
    std::vector<bool> visited_nodes;
    std::queue<vertex> next_on_line;

    /*pick random vertex*/
    std::random_device dev;
    std::mt19937 rng(dev());
    // distribution in range [0, total_vertices)
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,total_vertices-1);
    _vertex = (vertex)dist6(rng);

    total_vertices = _graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);
    next_on_line.push(_vertex);

    /*in case we have separedted connected components*/
    /*loop through all of them*/
    for (int node = 0; node < total_vertices; ++node)
    {
        if (not visited_nodes[node])
        {
            visited_nodes[node] = true;
            std::cout << "visiting node: [";
            std::cout << node << "]" << std::endl;
            while (not next_on_line.empty())
            {
                vertex front_vertex = next_on_line.front();
                next_on_line.pop();
                
                /*visit all neighbor vertices*/
                for (auto next_vertex : _graph._graph[front_vertex])
                {
                    std::cout << "visiting node: [";
                    std::cout << next_vertex << "]" << std::endl;
                    visited_nodes[next_vertex] = true;
                    next_on_line.push(next_vertex);
                }
            }
        }
    }
}

/*dfs path all connected component*/
/*start traversing from random vertex*/
/*Print visited nodes to standard error channel*/
void dfs_path(const graph& _graph)
{
    int total_vertices;
    vertex _vertex;
    std::stack<vertex> next_on_line;
    std::vector<bool> visited_nodes;

    /*pick random vertex*/
    std::random_device dev;
    std::mt19937 rng(dev());
    // distribution in range [0, total_vertices)
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,total_vertices-1);
    _vertex = (vertex)dist6(rng);

    total_vertices = _graph.grade();
    visited_nodes = std::vector<bool> (total_vertices, false);
    next_on_line.push(_vertex);

    /*loop through all connected components*/
    for (int node = 0; node < total_vertices; ++node)
    {
        next_on_line.push(node);
        while (not next_on_line.empty())
        {
            vertex temp = next_on_line.top();
            next_on_line.pop();
            if (not visited_nodes[temp])
            {   
                /*neighbors has not been visited yet*/
                visited_nodes[temp] = true;
                std::cout << "visiting node: [";
                std::cout << temp << "]" << std::endl;
                for (auto adjacent : _graph._graph[temp]) 
                    next_on_line.push(adjacent);
            }
        }
    }
}