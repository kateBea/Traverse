/**
 * @file procedures.h
 * @author kate (zanetty54@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <graph.h>

/*true if theres path from frist vertex to second (implements bfs)*/
bool bfs_to_target(const graph&, vertex, vertex);
/*true if theres path from frist vertex to second (implements dfs)*/
bool dfs_to_target(const graph&, vertex, vertex);

/*bfs path starting from given vertex*/
std::list<vertex> bfs_path(const graph&, vertex);
/*dfs path starting from given vertex*/
std::list<vertex> dfs_path(const graph&,vertex);

/*bfs path all connex component*/
void bfs_path(const graph&);
/*dfs path all connex component*/
void dfs_path(const graph&);