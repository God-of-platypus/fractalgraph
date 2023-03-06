#include "graph.hh"

FractalGraph::FractalGraph(unsigned int number_vertexes, unsigned int number_intern_graph)
        : number_vertexes_(number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        for (unsigned int j = 0; j < length; j++) {
            line.push_back(0);
        }
        adjacency_matrix_.push_back(line);
    }
}

void FractalGraph::add_edge(graphEdge edge) {
    unsigned int start_position = edge.start_node.vertex_num + number_vertexes_ * edge.start_node.graph_num;
    unsigned int end_position = edge.end_node.vertex_num + number_vertexes_ * edge.end_node.graph_num;
    this->adjacency_matrix_[start_position][end_position] = 1;
    this->adjacency_matrix_[end_position][start_position] = 1;
}

FractalGraph::FractalGraph(unsigned int number_vertexes, unsigned int number_intern_graph, graphEdge *edges,
                           size_t nb_edges)
        : number_vertexes_(number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        for (unsigned int j = 0; j < length; j++) {
            line.push_back(0);
        }
        adjacency_matrix_.push_back(line);
    }

    for (size_t i = 0; i < nb_edges; i++) {
        this->add_edge(edges[i]);
    }
}

FractalGraph::FractalGraph(unsigned int number_vertexes, unsigned int number_intern_graph,
                           std::vector<graphEdge> &edges)
        : number_vertexes_(number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        for (unsigned int j = 0; j < length; j++) {
            line.push_back(0);
        }
        adjacency_matrix_.push_back(line);
    }

    for (const auto it: edges) {
        this->add_edge(it);
    }
}

std::vector<Node> FractalGraph::get_adjacency_list(Node node) const {
    unsigned int pos = node.vertex_num + number_vertexes_ * node.graph_num;
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    std::vector<Node> res;
    for (unsigned int i = 0; i < length; i++) {
        if (this->adjacency_matrix_[pos][i]) {
            res.push_back({i % number_vertexes_, i / number_vertexes_});
        }
    }
    return res;
}

std::vector<std::vector<Node>> FractalGraph::get_all_adjacency_lists() const {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    std::vector<std::vector<Node>> res;
    for (unsigned )
}