# BFS and DFS test
Small program with C++ to test BFS and DFS traverse on 
graphs implemented as adjacency lists. There are still changes to be done.

# Graph test
Important NOTE: The graph is assumed to be directed, i.e say
we have a graph with 3 nodes {0, 1, 2}, insert edge (1,2)
means we want to add an edge from vertex 1 to vertex 2 to the graph.

Example usage included in file [main.cc](src/main.cc):

```cc
    // create a new graph with 
    // nodes_count amount of vertices
    graph gph(nodes_count);

    std::cout << "graph size: " << gph.size() << '\n';
    std::cout << "graph degree: " << gph.grade() << '\n';

    std::cout << "\nAdding edges to the graph" << '\n';
    std::cout << "-------------------------------------------------------" << '\n';

    // add edges to the graph
    for (const auto& edg : edges)
        gph.add_edge(edg);

    if (gph.empty())    
        std::cout << "graph is empty" << '\n';
    else
        std::cout << "graph is not empty" << '\n';

    std::cout << "print the graph" << '\n';
    std::cout << gph << '\n';

    std::cout << "path followed with dfs" << '\n';
    dfs_path(gph);
    
    std::cout << '\n';

    std::cout << "path followed with bfs" << '\n';
    bfs_path(gph);
```

Click [here](https://github.com/kateBea/Traverse/blob/main/src/graphs/grap_1.txt) for the graph example file used, and [here](image/graph_sample_2_test_procedures.png) its corresponding graphic representation.


# Example building and execution on linux:
```
git clone repo
cd Traverse/src

mkdir build
cd build
cmake ..
make

./traverse path_to_graph_file
```
Graph picture made with (can use to visualize graphs): [Graph Editor](https://csacademy.com/app/graph_editor/)
