#include <iostream>
#include "graph.hh"
#include "Directed.hh"

void print_path(std::vector<Node> nodes) {
    size_t n = nodes.size();
    for (size_t i = 0; i < n; i++) {
        std::cout << "(" << nodes[i].vertex_num << ", " << nodes[i].graph_num << ")";
        if (i < n - 1) {
            std::cout << " --> ";
        }
    }
    std::cout << "\n";
}

void test1() {
    FractalGraph fractalGraph(2, 2);
    fractalGraph.add_edge({{0, 0},
                           {0, 1}});
    fractalGraph.add_edge({{1, 0},
                           {1, 1}});
    fractalGraph.add_edge({{1, 1},
                           {0, 1}});
    fractalGraph.print_adjacency_matrix();
    std::cout << "------------------------------------------------------------\n";

    fractalGraph.print_adjacency_lists();
    std::cout << "------------------------------------------------------------\n";


    auto path = fractalGraph.dfs_path({0, 0}, {0, 1});
    auto b = fractalGraph.dfs({0, 0}, {0, 1});
    auto c = fractalGraph.bfs({0, 0}, {0, 1});
    if (!path.empty() && b && c) {
        std::cout << "OK: There is a path between (0,0) and (0,1)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (0,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({0, 0}, {1, 0});
    b = fractalGraph.dfs({0, 0}, {1, 0});
    c = fractalGraph.bfs({0, 0}, {1, 0});
    if (!path.empty() && b && c) {
        std::cout << "OK: There is a path between (0,0) and (1,0)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({1, 0}, {0, 0});
    b = fractalGraph.dfs({1, 0}, {0, 0});
    c = fractalGraph.bfs({1, 0}, {0, 0});
    if (!path.empty() && b && c ) {
        std::cout << "OK: There is a path between (1,0) and (0,0)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (1,0) and (0,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({1, 0}, {0, 1});
    b = fractalGraph.dfs({1, 0}, {0, 1});
    c = fractalGraph.bfs({1, 0}, {0, 1});
    if (!path.empty() && b && c) {
        std::cout << "OK: There is a path between (1,0) and (0,1)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (1,0) and (0,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({0, 0}, {1, 1});
    b = fractalGraph.dfs({0, 0}, {1, 1});
    c = fractalGraph.bfs({0, 0}, {1, 1});
    if (!path.empty() && b && c) {
        std::cout << "OK: There is a path between (0,0) and (1,1)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({1, 0}, {0, 2});
    b = fractalGraph.dfs({1, 0}, {0, 2});
    c = fractalGraph.bfs({1, 0}, {0, 2});
    if (!path.empty() || b || c) {
        std::cout << "KO: There is a path between (1,0) and (0,2)\n";
    } else {
        std::cout << "OK: There isn't a path between (1,0) and (0,2)\n";
    }
}

void test2() {
    FractalGraph fractalGraph(3, 2);
    fractalGraph.add_edge({{0, 0},
                           {1, 1}});
    fractalGraph.add_edge({{1, 0},
                           {2, 1}});
    fractalGraph.add_edge({{2, 0},
                           {0, 1}});
    fractalGraph.add_edge({{0, 0},
                           {2, 2}});
    fractalGraph.add_edge({{1, 0},
                           {0, 2}});
    fractalGraph.add_edge({{2, 0},
                           {1, 2}});
    fractalGraph.add_edge({{2, 1},
                           {1, 1}});
    fractalGraph.print_adjacency_lists();
    auto path = fractalGraph.dfs_path({0, 0}, {1, 0});
    bool b = fractalGraph.dfs({0, 0}, {1, 0});
    bool c = fractalGraph.bfs({0, 0}, {1, 0});
    std::cout << "------------------------------------------------------------\n";
    if (!path.empty() && b && c) {
        std::cout << "OK: There is a path between (0,0) and (1,0)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({0, 0}, {1, 1});
    b = fractalGraph.dfs({0,0}, {1,1});
    c = fractalGraph.bfs({0,0}, {1,1});
    if (!path.empty() && b && c) {
        std::cout << "OK: There is a path between (0,0) and (1,1)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({2, 0}, {0, 0});
    if (!path.empty()) {
        std::cout << "OK: There is a path between (2,0) and (0,0)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (2,0) and (0,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({2, 0}, {0, 2});
    if (!path.empty()) {
        std::cout << "OK: There is a path between (2,0) and (0,2)\n";
        std::cout << "------------------------------------------------------------\n";
        print_path(path);
    } else {
        std::cout << "KO: There isn't a path between (2,0) and (0,0)\n";
    }

}

void test3() {
    FractalGraph fg(2, 2);

    fg.add_edge({{0, 0},
                 {0, 1}});
    fg.add_edge({{1, 1},
                 {0, 2}});
    fg.add_edge({{1, 2},
                 {1, 0}});

    fg.print_adjacency_lists();
    std::cout << "------------------------------------------------------------\n";
    if (fg.dfs({0, 0}, {1, 0})) {
        std::cout << "KO: There is a path between (0,0) and (1,0)\n";
    } else {
        std::cout << "OK: There isn't a path between (0,0) and (1,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    if (fg.dfs({0, 0}, {1, 1})) {
        std::cout << "KO: There is a path between (0,0) and (1,1)\n";
    } else {
        std::cout << "OK: There isn't a path between (0,0) and (1,1)\n";
    }

}

void test4() {
    FractalGraph fg(7, 0);
    for (unsigned int i = 0; i < 7; i += 1) {
        for (unsigned int j = i + 1; j < 7; j += 3) {
            fg.add_edge({{i, 0}, {j, 0}});
        }
    }
    fg.print_adjacency_lists();
    std::cout << "------------------------------------------------------------\n";
    for (unsigned int i = 0; i < 7; i++) {
        for (unsigned int j = i + 1; j < 7; j++) {
            auto path = fg.dfs_path({i, 0}, {j, 0});
            if (path.empty()) {
                std::cout << "There isn't a path between (" << i << ",0) and (" << j << ",0)\n";
            } else {
                std::cout << "There is a path between (" << i << ",0) and (" << j << ",0)\n";
                std::cout << "------------------------------------------------------------\n";
                print_path(path);
            }
            std::cout << "------------------------------------------------------------\n";
        }
    }
}

void test5() {
    DirectedGraph dgf(2,1);
    dgf.add_edge({{0,0}, {0,1}});
    dgf.add_edge({{0,1}, {1,1}});
    dgf.add_edge({{1,1}, {1,0}});
    dgf.print_adjacency_matrix();
    if (dgf.dfs({1,0}, {0,0})) {
        std::cout << "KO: There is a path between (1,0) and (0,0)\n";
    } else {
        std::cout << "OK: There isn't a path between (1,0) and (0,0)\n";
    }
    auto path = dgf.dfs_path({0,0},{1,0});
    if (!path.empty()) {
        std::cout << "OK: There is a path between (1,0) and (0,0)\n";
        print_path(path);
    } else {
        std::cout << "KO\n";
    }
}

int main() {
    std::cout << "test 1 \n\n";
    test1();

    std::cout << "------------------------------------------------------------\ntest 2 \n\n";
    test2();

    std::cout << "------------------------------------------------------------\ntest 3\n\n";
    test3();

    std::cout << "------------------------------------------------------------\ntest 4\n\n";
    test4();

    std::cout << "------------------------------------------------------------\ntest 5\n\n";
    test5();
}