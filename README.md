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
```
If you want to add a list of edge, you do the following.
```c++
fg.add_edges(edges);
```
You could also create a fractal graph like this, if you already defined a list of edge.
```c++
FractalGraph fg = new FractalGraph(6,5,edges);
```
A fractal graph with random edges can be created like this.
```c++
FractalGraph fg = new FractalGraph(6,5,10);
```
