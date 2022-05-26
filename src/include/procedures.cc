#include <procedures.h>

/*true if theres path from frist vertex to second (implements bfs)*/
bool bfs_to_target(const graph&, vertex, vertex);
/*true if theres path from frist vertex to second (implements dfs)*/
bool dfs_to_target(const graph&, vertex, vertex);

/*bfs path starting from given vertex*/
void bfs_path(const graph&, vertex);
/*dfs path starting from given vertex*/
void dfs_path(const graph&,vertex);

/*bfs path all connex component*/
void bfs_path(const graph&);
/*dfs path all connex component*/
void dfs_path(const graph&);