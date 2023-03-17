#include <iostream>
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
    if (edge.start_node.vertex_num >= number_vertexes_) {
        throw std::out_of_range("The vertex of starting node is out of bound\n");
    }
    if (edge.end_node.vertex_num >= number_vertexes_) {
        throw std::out_of_range("The vertex of ending node is out of bound\n");
    }
    if (edge.start_node.graph_num > number_intern_graph_) {
        throw std::out_of_range("The intern graph number of starting node is out of bound\n");
    }
    if (edge.end_node.graph_num > number_intern_graph_) {
        throw std::out_of_range("The intern graph number of ending node is out of bound\n");
    }
    unsigned int start_position = edge.start_node.vertex_num + number_vertexes_ * edge.start_node.graph_num;
    unsigned int end_position = edge.end_node.vertex_num + number_vertexes_ * edge.end_node.graph_num;

    this->adjacency_matrix_[start_position][end_position] = 1;
    this->adjacency_matrix_[end_position][start_position] = 1;
}

void FractalGraph::add_edges(std::vector<graphEdge> &edges) {
    for (const auto &it: edges) {
        add_edge(it);
    }
}

FractalGraph::FractalGraph(unsigned int number_vertexes, unsigned int number_intern_graph, graphEdge *edges,
                           std::size_t nb_edges)
        : number_vertexes_(number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        for (unsigned int j = 0; j < length; j++) {
            line.push_back(0);
        }
        adjacency_matrix_.push_back(line);
    }

    for (std::size_t i = 0; i < nb_edges; i++) {
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
    for (unsigned int i = 0; i < length; i++) {
        res.push_back(get_adjacency_list({i % number_vertexes_, i / number_vertexes_}));
    }
    return res;
}

void FractalGraph::print_adjacency_matrix() const {
    for (const auto &it: adjacency_matrix_) {
        for (const auto &i: it) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
}

void FractalGraph::print_adjacency_lists() const {
    auto list = get_all_adjacency_lists();
    for (unsigned int i = 0; i < list.size(); i++) {
        std::cout << "List of adjacency of node { " << i % number_vertexes_ << ", " << i / number_vertexes_ << " } :";
        for (auto &j: list[i]) {
            std::cout << " { " << j.vertex_num << ", " << j.graph_num << " }";
        }
        std::cout << '\n';
    }
}

static bool find_node(const Node node, const std::vector<Node> &nodes) {
    for (const auto &n: nodes) {
        if (n.vertex_num == node.vertex_num && n.graph_num == node.graph_num) {
            return true;
        }
    }
    return false;
}

static std::vector<Node> filter_same_graph(unsigned int graph_num, const std::vector<Node> &nodes) {
    std::vector<Node> res;
    for (const auto &node: nodes) {
        if (node.graph_num == graph_num) {
            res.push_back(node);
        }
    }
    return res;
}

bool FractalGraph::dfs(Node start, Node end, std::vector<unsigned int> depth) const {
    if (start.vertex_num == end.vertex_num && start.graph_num == end.graph_num) {
        return true;
    }
    auto list_start = this->get_adjacency_list(start);
    auto list_end = this->get_adjacency_list(end);
    if (start.graph_num != end.graph_num)
    {
        auto new_start = filter_same_graph(end.graph_num, list_start);
        auto new_end = filter_same_graph(start.graph_num, list_end);
        if (!new_start.empty())
        {
            for (const auto& node: new_start)
            {
                auto new_depth = depth;
                new_depth.push_back(node.graph_num);
                if (dfs(node, end, new_depth))
                {
                    return true;
                }
            }
        }
        else if (!new_end.empty())
        {
            for (const auto& node: new_end)
            {
                auto new_depth = depth;
                new_depth.push_back(node.graph_num);
                if (dfs(start, node, new_depth))
                {
                    return true;
                }
            }
        }
        else
        {
            for (const auto& node_start: list_start)
            {
                auto new_end2 = filter_same_graph(node_start.graph_num, list_end);
                for (const auto& node_end: new_end2)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if (!depth.empty()) {
        Node prev_level = {start.vertex_num, depth.back()};
        auto list = this->get_adjacency_list(prev_level);
        Node prev_end = {end.vertex_num, depth.back()};
        if (find_node(prev_end, list)) {
            return true;
        }
    }
    if (depth.size() >= this->number_vertexes_ * this->number_vertexes_) {
        return false;
    }
    for (const auto &node: list_start) {
        auto list_filter = filter_same_graph(node.graph_num, list_end);
        if (list_filter.empty())
        {
            for (const auto& node_end: list_end)
            {
                if (dfs(node, node_end, depth))
                {
                    return true;
                }
            }
        } else {
            for (const auto &node_end: list_filter) {
                auto new_depth = depth;
                new_depth.push_back(node.graph_num);
                if (dfs({node.vertex_num, 0}, {node_end.vertex_num, 0}, new_depth)) {
                    return true;
                }
            }
        }
    }
    return false;
}
