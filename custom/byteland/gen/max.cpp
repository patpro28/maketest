#include <cstdlib>
#include "graph.h"
#include "../params.h"

int main(int, char* argv[]) {
    int seed = std::atoi(argv[1]);
    Random gen(seed);
    const int n = N_MAX;
    if (seed == 0) {
        generate_graph(gen, {n}, n - 1, false, true);
    } else if (seed == 1) {
        generate_graph(gen, {1, n - 1}, M_MAX, false, false);
    } else if (seed == 2) {
        generate_graph(gen, {60000, 40000}, M_MAX, false, false);
    } else if (seed == 3) {
        generate_graph(gen, {3, 50000, 49997}, M_MAX, false, false);
    } else if (seed == 4) {
        generate_graph(gen, std::vector<int>(n / 2, 2), n / 2, true, false);
    } else {
        std::vector<int> sizes(n - 2, 1);
        sizes.push_back(2);
        generate_graph(gen, sizes, 1, false, false);
    }
}
