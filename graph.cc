#include <iostream>
#include <map>
#include <utility>
#include <queue>
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

FractalGraph::FractalGraph(unsigned int number_vertexes, unsigned int number_intern_graph, unsigned int nb_edges)
        : number_vertexes_(number_vertexes), number_intern_graph_(number_intern_graph) {
    unsigned int length = number_vertexes_ * (number_intern_graph_ + 1);
    for (unsigned int i = 0; i < length; i++) {
        std::vector<int> line;
        for (unsigned int j = 0; j < length; j++) {
            line.push_back(0);
        }
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

inline bool equal_node(Node node1, Node node2) {
    return node1.graph_num == node2.graph_num && node1.vertex_num == node2.vertex_num;
}

bool equal_edges(graphEdge edge1, graphEdge edge2) {
    return equal_node(edge1.start_node, edge2.start_node) && equal_node(edge1.end_node, edge2.end_node);
}

static bool
checkMap(std::multimap<std::vector<unsigned int>, graphEdge> map, std::vector<unsigned int> depth, graphEdge edge) {
    auto range = map.equal_range(depth);
    for (auto i = range.first; i != range.second; i++) {
        if (equal_edges(edge, i->second)) {
            return true;
        }
    }
    return false;
}

bool FractalGraph::dfs(Node start, Node end, const std::vector<unsigned int> &depth,
                       std::multimap<std::vector<unsigned int>, graphEdge> map) const {
    if (equal_node(start, end)) {
        return true;
    }

    if (checkMap(map, depth, {start, end})) {
        return false;
    }

    auto list_start = this->get_adjacency_list(start);
    auto list_end = this->get_adjacency_list(end);
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

bool FractalGraph::dfs(Node start, Node end) const {
    std::multimap<std::vector<unsigned int>, graphEdge> map;
    std::vector<unsigned int> depth;
    return dfs(start, end, depth, map);
}

std::vector<Node> FractalGraph::dfs_path(Node start, Node end, const std::vector<unsigned int> &depth,
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
    auto list_end = this->get_adjacency_list(end);
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

std::vector<Node> FractalGraph::dfs_path(Node start, Node end) const {
    std::multimap<std::vector<unsigned int>, graphEdge> map;
    std::vector<unsigned int> depth;
    return dfs_path(start, end, depth, map);
}

bool FractalGraph::bfs(Node start, Node end) const {
    std::queue<std::pair<std::vector<unsigned int>, graphEdge>> queue;
    std::multimap<std::vector<unsigned int>, graphEdge> map;
    std::vector<unsigned int> depth;
    queue.push({depth, {start, end}});
    while (!queue.empty()) {
        auto pair = queue.front();
        queue.pop();
        auto new_depth = pair.first;
        Node start_node = pair.second.start_node;
        Node end_node = pair.second.end_node;
        if (checkMap(map, new_depth, {start_node, end_node}))
        {
            continue;
        }
        if (equal_node(start_node, end_node)) {
            return true;
        }
        auto list_start = this->get_adjacency_list(start_node);
        auto list_end = this->get_adjacency_list(end_node);
        if (start_node.graph_num != end_node.graph_num) {
            auto new_start = filter_same_graph(end_node.graph_num, list_start);
            auto new_end = filter_same_graph(start_node.graph_num, list_end);
            if (!new_start.empty()) {
                for (const auto &node_new_start: new_start) {
                    auto ndepth = new_depth;
                    ndepth.push_back(node_new_start.graph_num);
                    queue.push({ndepth, {{node_new_start.vertex_num, 0}, {end_node.vertex_num, 0}}});
                }
            } else if (!new_end.empty()) {
                for (const auto &node_new_end: new_end) {
                    auto ndepth = new_depth;
                    ndepth.push_back(node_new_end.graph_num);
                    queue.push({ndepth, {{start_node.vertex_num, 0}, {node_new_end.vertex_num, 0}}});
                }
            } else {
                for (const auto &node_new_start: new_start) {
                    auto filtered_end = filter_same_graph(node_new_start.graph_num, new_start);
                    for (const auto &node_new_end: filtered_end) {
                        auto ndepth = new_depth;
                        ndepth.push_back(node_new_start.graph_num);
                        queue.push({ndepth, {{node_new_start.vertex_num, 0}, {node_new_end.vertex_num, 0}}});
                    }
                }
            }
        }
        if (!new_depth.empty()) {
            Node previous_level_start = {start_node.vertex_num, new_depth.back()};
            auto list_prev = this->get_adjacency_list(previous_level_start);
            Node previous_level_end = {end_node.vertex_num, new_depth.back()};
            if (find_node(previous_level_end, list_prev)) {
                return true;
            }
        }
        if (new_depth.size() > this->number_vertexes_ * this->number_vertexes_) {
            map.insert({new_depth, {start_node, end_node}});
            continue;
        }
        for (const auto &node_new_start: list_start){
            auto filtered_end = filter_same_graph(node_new_start.graph_num, list_end);
            for (const auto &node_new_end: filtered_end) {
                auto ndepth = new_depth;
                ndepth.push_back(node_new_start.graph_num);
                queue.push({ndepth, {{node_new_start.vertex_num, 0}, {node_new_end.vertex_num, 0}}});
            }
        }
        map.insert({new_depth, {start_node, end_node}});
    }
    return false;
}