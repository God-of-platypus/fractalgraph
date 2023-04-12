#pragma once

#include <vector>
#include <map>
#include <random>

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

    void add_edges(std::vector<graphEdge>& edges);

    FractalGraph(unsigned int number_vertexes, unsigned int  number_intern_graph, graphEdge edges[], std::size_t nb_edges);

    FractalGraph(unsigned int number_vertexes, unsigned int  number_intern_graph, std::vector<graphEdge>& edges);


    FractalGraph(unsigned int number_vertexes, unsigned int number_intern_graph, unsigned int nb_edges);

    [[nodiscard]] std::vector<Node> get_adjacency_list(Node node) const;

    [[nodiscard]] std::vector<std::vector<Node>> get_all_adjacency_lists() const;

    void print_adjacency_matrix() const;

    void print_adjacency_lists() const;

    [[nodiscard]] bool dfs(Node start, Node end) const;

    [[nodiscard]] std::vector<Node> dfs_path(Node start, Node end) const;

    [[nodiscard]] bool bfs(Node start, Node end) const;

private:
    const unsigned int number_vertexes_;
    const unsigned int number_intern_graph_;
    std::vector<std::vector<int>> adjacency_matrix_;
    [[nodiscard]] bool dfs(Node start, Node end,const std::vector<unsigned int>& depth, std::multimap<std::vector<unsigned int>,graphEdge> map) const;
    [[nodiscard]] std::vector<Node> dfs_path(Node start, Node end, const std::vector<unsigned int>& depth, std::multimap<std::vector<unsigned int>,graphEdge>& map) const;
};

