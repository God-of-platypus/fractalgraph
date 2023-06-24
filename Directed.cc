//
// Created by stan on 29/05/23.
//



#include "Directed.hh"

DirectedGraph::DirectedGraph(unsigned int number_vertexes, unsigned int number_intern_graph) : number_vertexes_(
        number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        line.resize(length, 0);
        adjacency_matrix_.push_back(line);
    }
}

void DirectedGraph::add_edge(graphEdge edge) {
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
}

void DirectedGraph::add_edges(std::vector<graphEdge> &edges) {
    for (const auto &it: edges) {
        add_edge(it);
    }
}

DirectedGraph::DirectedGraph(unsigned int number_vertexes, unsigned int number_intern_graph,
                             std::vector<graphEdge> &edges) : number_vertexes_(
        number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        line.resize(length, 0);
        adjacency_matrix_.push_back(line);
    }
    add_edges(edges);
}

DirectedGraph::DirectedGraph(unsigned int number_vertexes, unsigned int number_intern_graph, graphEdge *edges,
                             std::size_t nb_edges) : number_vertexes_(
        number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        line.resize(length, 0);
        adjacency_matrix_.push_back(line);
    }
    for (size_t i = 0; i < nb_edges; ++i) {
        add_edge(edges[i]);
    }
}

DirectedGraph::DirectedGraph(unsigned int number_vertexes, unsigned int number_intern_graph, unsigned int nb_edges)
        : number_vertexes_(
        number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        line.resize(length, 0);
        adjacency_matrix_.push_back(line);
    }

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertexes(0, number_vertexes_ - 1);
    std::uniform_int_distribution<> intern_graphs(0, number_intern_graph_);
    for (unsigned int i = 0; i < nb_edges; i++) {
        unsigned int a = vertexes(gen);
        unsigned int b = intern_graphs(gen);
        unsigned int c = vertexes(gen);
        unsigned int d = intern_graphs(gen);
        this->add_edge({{a, b},
                        {c, d}});
    }
}

std::vector<Node> DirectedGraph::get_adjacency_list(Node node) const {
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

std::vector<std::vector<Node>> DirectedGraph::get_all_adjacency_lists() const {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    std::vector<std::vector<Node>> res;
    for (unsigned int i = 0; i < length; i++) {
        res.push_back(get_adjacency_list({i % number_vertexes_, i / number_vertexes_}));
    }
    return res;
}

void DirectedGraph::print_adjacency_matrix() const {
    for (const auto &it: adjacency_matrix_) {
        for (const auto &i: it) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
}

void DirectedGraph::print_adjacency_lists() const {
    auto list = get_all_adjacency_lists();
    for (unsigned int i = 0; i < list.size(); i++) {
        std::cout << "List of adjacency of node { " << i % number_vertexes_ << ", " << i / number_vertexes_ << " } :";
        for (auto &j: list[i]) {
            std::cout << " { " << j.vertex_num << ", " << j.graph_num << " }";
        }
        std::cout << '\n';
    }
}

std::vector<Node> DirectedGraph::reverse(Node node) const {
    std::vector<Node> nodes;
    unsigned int pos = node.vertex_num + number_vertexes_ * node.graph_num;
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        if (this->adjacency_matrix_[i][pos]) {
            nodes.push_back({i % number_vertexes_, i / number_vertexes_});
        }
    }
    return nodes;
}

bool DirectedGraph::dfs(Node start, Node end) const {
    std::vector<unsigned int> depth;
    std::multimap<std::vector<unsigned int>, graphEdge> map;
    return dfs(start, end, depth, map);
}

bool DirectedGraph::dfs(Node start, Node end, const std::vector<unsigned int> &depth,
                        std::multimap<std::vector<unsigned int>, graphEdge> &map) const {
    if (equal_node(start, end)) {
        return true;
    }
    if (checkMap(map, depth, {start, end})) {
        return false;
    }
    auto list_start = get_adjacency_list(start);
    auto list_end = reverse(end);
    if (start.graph_num != end.graph_num) {
        auto new_start = filter_same_graph(end.graph_num, list_start);
        auto new_end = filter_same_graph(start.graph_num, list_end);
        if (!new_start.empty()) {
            for (const auto &node: new_start) {
                auto new_depth = depth;
                new_depth.push_back(node.graph_num);
                if (dfs({node.vertex_num, 0}, {end.vertex_num, 0}, new_depth, map)) {
                    return true;
                }
            }
        } else if (!new_end.empty()) {
            for (const auto &node: new_end) {
                auto new_depth = depth;
                new_depth.push_back(node.graph_num);
                if (dfs({start.vertex_num, 0}, {node.vertex_num, 0}, new_depth, map)) {
                    return true;
                }
            }
        } else {
            for (const auto &node_start: list_start) {
                auto new_end2 = filter_same_graph(node_start.graph_num, list_end);
                for (const auto &node_end: new_end2) {
                    if (dfs(node_start, node_end, depth, map)) {
                        return true;
                    }
                }
            }
        }
        map.insert({depth, {start, end}});
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
        map.insert({depth, {start, end}});
        return false;
    }
    for (const auto &node: list_start) {
        auto list_filter = filter_same_graph(node.graph_num, list_end);
        for (const auto &node_end: list_filter) {
            auto new_depth = depth;
            new_depth.push_back(node.graph_num);
            if (dfs({node.vertex_num, 0}, {node_end.vertex_num, 0}, new_depth, map)) {
                return true;
            }
        }

    }
    map.insert({depth, {start, end}});
    return false;
}

std::vector<Node> DirectedGraph::dfs_path(Node start, Node end) const {
    std::multimap<std::vector<unsigned int>, graphEdge> map;
    std::vector<unsigned int> depth;
    return dfs_path(start, end, depth, map);
}

std::vector<Node> DirectedGraph::dfs_path(Node start, Node end, const std::vector<unsigned int> &depth,
                                          std::multimap<std::vector<unsigned int>, graphEdge> &map) const {
    if (equal_node(start, end)) {
        if (depth.empty()) {
            return {start};
        } else {
            return {{start.vertex_num, depth.back()}};
        }
    }

    if (checkMap(map, depth, {start, end})) {
        return {};
    }

    auto list_start = this->get_adjacency_list(start);
    auto list_end = reverse(end);
    if (find_node(start, list_end)) {
        if (depth.empty()) {
            return {start, end};
        } else {
            return {{start.vertex_num, depth.back()},
                    {end.vertex_num,   depth.back()}};
        }
    }
    if (start.graph_num != end.graph_num) {
        auto new_start = filter_same_graph(end.graph_num, list_start);
        auto new_end = filter_same_graph(start.graph_num, list_end);
        if (!new_start.empty()) {
            for (const auto &node: new_start) {
                auto new_depth = depth;
                if (node.graph_num != 0)
                    new_depth.push_back(node.graph_num);
                auto path = dfs_path({node.vertex_num, 0}, {end.vertex_num, 0}, new_depth, map);
                if (!path.empty()) {
                    if (depth.empty()) {
                        path.insert(path.begin(), start);
                    } else {
                        path.insert(path.begin(), {start.vertex_num, depth.back()});
                    }
                    return path;
                }

            }
        } else if (!new_end.empty()) {
            for (const auto &node: new_end) {
                auto new_depth = depth;
                new_depth.push_back(node.graph_num);
                auto path = dfs_path({start.vertex_num, 0}, {node.vertex_num, 0}, new_depth, map);
                if (!path.empty()) {
                    if (depth.empty()) {
                        path.push_back(end);
                    } else {
                        path.push_back({end.vertex_num, depth.back()});
                    }
                    return path;
                }
            }
        } else {
            for (const auto &node_start: list_start) {
                auto new_end2 = filter_same_graph(node_start.graph_num, list_end);
                for (const auto &node_end: new_end2) {
                    auto path = dfs_path(node_start, node_end, depth, map);
                    if (!path.empty()) {
                        path.insert(path.begin(), start);
                        path.push_back(end);
                        return path;
                    }
                }
            }
        }
        map.insert({depth, {start, end}});
        return {};
    }
    if (!depth.empty()) {
        Node prev_level = {start.vertex_num, depth.back()};
        auto list = this->get_adjacency_list(prev_level);
        Node prev_end = {end.vertex_num, depth.back()};
        if (find_node(prev_end, list)) {
            return {prev_level, prev_end};
        }
    }
    if (depth.size() >= this->number_vertexes_ * this->number_vertexes_) {
        map.insert({depth, {start, end}});
        return {};
    }
    for (const auto &node: list_start) {
        auto list_filter = filter_same_graph(node.graph_num, list_end);
        for (const auto &node_end: list_filter) {
            auto new_depth = depth;
            if (node.graph_num != 0)
                new_depth.push_back(node.graph_num);
            auto path = dfs_path({node.vertex_num, 0}, {node_end.vertex_num, 0}, new_depth, map);
            if (!path.empty()) {
                if (depth.empty()) {
                    path.insert(path.begin(), start);
                    path.push_back(end);
                } else {
                    path.insert(path.begin(), {start.vertex_num, depth.back()});
                    path.push_back({end.vertex_num, depth.back()});
                }
                return path;
            }
        }

    }
    map.insert({depth, {start, end}});
    return {};
}