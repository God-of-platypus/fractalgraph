#include <iostream>
#include "graph.hh"

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
    size_t n = path.size();
    if (!path.empty()) {
        std::cout << "OK: There is a path between (0,0) and (0,1)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (0,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({0, 0}, {1, 0});
    n = path.size();
    if (!path.empty()) {
        std::cout << "OK: There is a path between (0,0) and (1,0)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({1, 0}, {0, 0});
    n = path.size();
    if (!path.empty()) {
        std::cout << "OK: There is a path between (1,0) and (0,0)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (1,0) and (0,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({1, 0}, {0, 1});
    n = path.size();
    if (!path.empty()) {
        std::cout << "OK: There is a path between (1,0) and (0,1)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (1,0) and (0,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({0, 0}, {1, 1});
    n = path.size();
    if (!path.empty()) {
        std::cout << "OK: There is a path between (0,0) and (1,1)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    if (fractalGraph.dfs({1, 0}, {0, 2})) {
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
    size_t n = path.size();
    std::cout << "------------------------------------------------------------\n";
    if (!path.empty()) {
        std::cout << "OK: There is a path between (0,0) and (1,0)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({0,0}, {1, 1});
    n = path.size();
    if (n != 0) {
        std::cout << "OK: There is a path between (0,0) and (1,1)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (0,0) and (1,1)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({2, 0}, {0, 0});
    n = path.size();
    if (!path.empty()) {
        std::cout << "OK: There is a path between (2,0) and (0,0)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "KO: There isn't a path between (2,0) and (0,0)\n";
    }

    std::cout << "------------------------------------------------------------\n";
    path = fractalGraph.dfs_path({2, 0}, {0, 2});
    n = path.size();
    if (!path.empty()) {
        std::cout << "OK: There is a path between (2,0) and (0,2)\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < n; i++) {
            std::cout << "(" << path[i].vertex_num << ", " << path[i].graph_num << ")";
            if (i < n - 1) {
                std::cout << " --> ";
            }
        }
        std::cout << "\n";
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

int main() {
    std::cout << "test 1 \n\n";
    test1();

    std::cout << "------------------------------------------------------------\ntest 2 \n\n";
    test2();

    std::cout << "------------------------------------------------------------\ntest 3\n\n";
    test3();
}