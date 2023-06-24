# Fractal Graph

A fractal graph is a graph with one or more copy of it inside itself.

##  Usage

An edge is represented by the struct graphEdge. Inside this struct we have the start and the end of the edges. The start and the end are represented by the struct Node. The Node struct is composed of 2 unsigned int, the first one represent the vertex we are using and the second one indicate which copie we are in.
```c++
#create a fractal graph with 5 copies and 6 vertices
FractalGraph fg(6,5);

#add an edge to fg
graphEdge edge = {{0,0},{0,1}};
fg.add_edge(edge);

#add a list of edge to fg
std::vector<graphEdge> edges = {{{0, 1}, {5, 5}}, {{0, 1}}, {4, 2}};
fg.add_edges(edges);

#creating a ractal graph with 5 copies and 6 vertices and with some edges
FractalGraph fg2(6, 5, edges);

#creating a ractal graph with 5 copies and 6 vertices and 100 random edges
FractalGraph fg3(6, 5, 100);

#checking if there is a path between 0_0 and 5_0 in fg3
bool res = fg3.dfs({0, 0}, {5, 0});

#getting the path between 0_0 and 5_0 in fg3
std::vector<Node> path = fg3.dfs_path({0, 0}, {5, 0});
```
For a directed fractal graph, you do the same with the class Directed 
