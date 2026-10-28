#include <cstdlib>
#include <iostream>
#include <vector>
#include "../params.h"

struct Op { char type; int u = 0, v = 0; };
int main(int argc, char **argv) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    if (seed < 0 || seed > 2) return 1;
    int q = int(Q_MAX);
    int blue = seed == 0 ? q / 2 : seed == 1 ? q * 2 / 5 : q / 2 - 500;
    int red = seed == 1 ? q / 5 : 1;
    int n = blue + red;
    std::vector<Op> ops;
    for (int v = 2; v <= blue; ++v) ops.push_back({'+', v, v - 1});
    for (int v = blue + 2; v <= n; ++v) ops.push_back({'+', v, v - 1});
    ops.push_back({'+', blue + 1, blue});
    for (int v = 3; v <= blue; ++v) ops.push_back({'+', v, 1});
    if (seed == 2) {
        for (int v = 3; v < 503; ++v) {
            ops.push_back({'-', 1, v});
            ops.push_back({'?'});
        }
        ops.push_back({'-', blue, blue + 1});
        ops.push_back({'?'});
    }
    while (int(ops.size()) < q) ops.push_back({'?'});
    if (int(ops.size()) != q || n > N_MAX) return 1;
    std::cout << n << ' ' << q << '\n';
    for (int i = 1; i <= n; ++i) std::cout << (i > 1 ? " " : "") << (i > blue ? 1 : 0);
    std::cout << '\n';
    for (auto op : ops) {
        std::cout << op.type;
        if (op.type != '?') std::cout << ' ' << op.u << ' ' << op.v;
        std::cout << '\n';
    }
}
