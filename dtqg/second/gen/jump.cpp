#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../params.h"

int main(int argc, char **argv) {
    const int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    const int n = N_MAX, m = n / 2;
    std::vector<int> a;
    for (int x = n - 1; x >= m; --x) a.push_back(x);
    a.push_back(n);
    for (int x = 1; x < m; ++x) a.push_back(x);
    // Mirror the same quadratic traversal to the left in the second case.
    if (seed == 1) std::reverse(a.begin(), a.end());
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << a[i];
    std::cout << '\n';
}
