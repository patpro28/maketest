#include "random.h"
#include "../params.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void emit(const string &s, int low, int high, int budget) {
    cout << s.size() << ' ' << low << ' ' << high << ' ' << budget << '\n' << s << '\n';
}

void maximum(int kind) {
    const int n = N_MAX;
    if (kind == 0) emit(string(n, '0'), 1, 3, 0);
    else if (kind == 1) emit(string(n, '1'), 1, n, 2);
    else if (kind == 2) emit(string(n, '9'), 1, n, 8);
    else emit(string(n, '0'), 2, 2, 0);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1 1 0\n0\n",
        "1 1 1 0\n1\n",
        "1 1 1 9\n9\n",
        "2 2 2 0\n00\n",
        "3 2 2 0\n000\n",
        "5 1 3 3\n11111\n",
        "5 1 3 4\n22222\n",
        "5 1 3 1\n01010\n",
        "5 2 4 9\n12345\n",
        "6 1 4 0\n000000\n",
        "4 1 4 9\n9999\n",
        "8 2 3 0\n00000000\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108452ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    int low = rng.uniform(1, min(n, 4));
    const auto digits = word("001223456789", n);
    const auto high = rng.uniform(low, n);
    const auto budget = rng.uniform(0, 9 * n);
    emit(digits, low, high, budget);
}
