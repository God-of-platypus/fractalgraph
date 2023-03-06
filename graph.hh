#pragma once

#include <vector>

struct Node {
    unsigned int vertex_num; // number between 0 and n-1
    unsigned int graph_num;  // number between 0 and k
};

struct graphEdge {
    Node start_node;
    Node end_node;
};


class FractalGraph {
public:
    FractalGraph(unsigned int number_vertexes, unsigned number_intern_graph);

    void add_edge(graphEdge edge);

    FractalGraph(unsigned int number_vertexes, unsigned number_intern_graph, graphEdge edges[], size_t nb_edges);

    FractalGraph(unsigned int number_vertexes, unsigned number_intern_graph, std::vector<graphEdge>& edges);

    [[nodiscard]] std::vector<Node> get_adjacency_list(Node node) const;

    [[nodiscard]] std::vector<std::vector<Node>> get_all_adjacency_lists() const;

private:
    const unsigned int number_vertexes_;
    const unsigned int number_intern_graph_;
    std::vector<std::vector<int>> adjacency_matrix_;
};

