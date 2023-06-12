//
// Created by stan on 29/05/23.
//

#ifndef FRACTALGRAPH_DIRECTED_HH
#define FRACTALGRAPH_DIRECTED_HH

#include "graph.hh"
#include <stdexcept>
#include <iostream>
#include <map>

class DirectedGraph {
public:
    DirectedGraph(unsigned int number_vertexes, unsigned number_intern_graph);

    void add_edge(graphEdge edge);

    void add_edges(std::vector<graphEdge> &edges);

    DirectedGraph(unsigned int number_vertexes, unsigned int number_intern_graph, graphEdge edges[],
                  std::size_t nb_edges);

    DirectedGraph(unsigned int number_vertexes, unsigned int number_intern_graph, std::vector<graphEdge> &edges);


    DirectedGraph(unsigned int number_vertexes, unsigned int number_intern_graph, unsigned int nb_edges);

    [[nodiscard]] std::vector<Node> get_adjacency_list(Node node) const;

    [[nodiscard]] std::vector<std::vector<Node>> get_all_adjacency_lists() const;

    void print_adjacency_matrix() const;

    void print_adjacency_lists() const;

    std::vector<Node> reverse(Node node) const;

    bool dfs(Node start, Node end) const;

    [[nodiscard]] std::vector<Node> dfs_path(Node start, Node end) const;

private:
    const unsigned int number_vertexes_;
    const unsigned int number_intern_graph_;
    std::vector<std::vector<int>> adjacency_matrix_;

    bool dfs(Node start, Node end, const std::vector<unsigned int> &depth,
             std::multimap<std::vector<unsigned int>, graphEdge> &map) const;

    [[nodiscard]] std::vector<Node> dfs_path(Node start, Node end, const std::vector<unsigned int> &depth,
                                             std::multimap<std::vector<unsigned int>, graphEdge> &map) const;
};


#endif //FRACTALGRAPH_DIRECTED_HH
