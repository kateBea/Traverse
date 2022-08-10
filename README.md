# BFS and DFS test
Some small scripts made on C++ to test BFS and DFS traverse on 
graphs implemented as adjacency lists. There's still some changes to be done.

# GRAPH DATA
You can visualize graph from the next url:
https://csacademy.com/app/graph_editor/

Important NOTE: The graph is assumed to be directed, i.e say
we have a graph with 3 nodes {0, 1, 2}, insert edge (1,2)
means there is an edge from vertex 1 to vertex 2, if we want the 
edge in the oposite direction we may add it using provided methods.
There is some scripts provided showing some small usage of the 
general class and the functions.

Here is a small example:

```cc
    std::cout << myGraph.size() << std::endl;
    std::cout << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    myGraph = graph(GRAPH_SIZE);
    for (const auto& _edges : graph_sample_2)
        myGraph.add_edge(_edges);

    std::cout << "This line comes after insertion of few edges into graph" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "graph has (" << myGraph.size() << ") edges"<< std::endl;
    std::cout << "graph grade is: " << myGraph.grade() << std::endl;

    if (myGraph.empty())    std::cout << "graph is empty" << std::endl;
    else                    std::cout << "graph is not empty" << std::endl;

    std::cout << "we print the graph" << std::endl;
    std::cout << myGraph << std::endl;

    std::cout << "path followed with dfs traversing" << std::endl; dfs_path(myGraph); std::cout << std::endl;
    std::cout << "path followed with bfs traversing" << std::endl; bfs_path(myGraph);
```

Graph picture made with: [Graph Editor](https://csacademy.com/app/graph_editor/)
