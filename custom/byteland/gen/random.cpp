#include <cstdlib>
#include "graph.h"
#include "../params.h"

int main(int, char* argv[]) {
    Random gen(std::atoll(argv[1]));
    int n = gen.uniform(1000, static_cast<int>(N_MAX));
    int k = gen.uniform(2, 30);
    std::vector<int> sizes(k, n / k);
    for (int i = 0; i < n % k; ++i) ++sizes[i];
    int m = gen.uniform(n - k, std::min(static_cast<int>(M_MAX), 2 * n));
    generate_graph(gen, sizes, m, true, false);
}
