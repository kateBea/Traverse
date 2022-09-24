# BFS and DFS test
Small program with C++ to test BFS and DFS traverse on 
graphs implemented as adjacency lists. There's still changes to be done.

# Graph test
Important NOTE: The graph is assumed to be directed, i.e say
we have a graph with 3 nodes {0, 1, 2}, insert edge (1,2)
means we want to add an edge from vertex 1 to vertex 2 to the graph.

Example usage included in file [main.cc](src/main.cc):

```cc
    std::size_t size {};
    std::vector<edge> graph_sample{};
    if (not file_setup(argv[1], graph_sample, size))
        return 1;

    graph myGraph(size);
    for (const auto& l_edges : graph_sample)
        myGraph.add_edge(l_edges);

    std::cout << "graph size: " << myGraph.size() << std::endl;
    std::cout << "graph degree: " << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;


    std::cout << "\nAfter adding few edges into the graph" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    std::cout << "print the graph" << std::endl;
    std::cout << myGraph << std::endl;

    std::cout << "path followed with dfs" << std::endl;
    dfs_path(myGraph);
    std::cout << std::endl;

    std::cout << "path followed with bfs" << std::endl;
    bfs_path(myGraph);
```

Click [here](https://github.com/kateBea/Traverse/blob/main/src/graphs/grap_1.txt) for the graph example file used, and [here](image/graph_sample_2_test_procedures.png) its corresponding graphic representation.


# Example building and execution on linux:
```
git clone repo
cd Traverse
cd src

mkdir build
cd build
cmake ..
make

./traverse path_to_graph_file
```
Graph picture made with (can use to visualize graphs): [Graph Editor](https://csacademy.com/app/graph_editor/)
