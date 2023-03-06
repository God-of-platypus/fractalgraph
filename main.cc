#include <iostream>
#include "graph.hh"

int main()
{
    FractalGraph fractalGraph(2, 2);
    graphEdge edge = {{0, 0}, {0 ,1 }};
    fractalGraph.add_edge(edge);
    auto test = fractalGraph.get_adjacency_list({0, 0});
    std::cout << test.size() << '\n';
    for (auto i : test)
    {
        std::cout << "vertex: " << i.vertex_num << " graph_num: " << i.graph_num << "\n";
    }
}