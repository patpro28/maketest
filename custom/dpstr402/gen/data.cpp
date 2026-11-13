#include "random.h"
#include "../params.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string cycle(const string &pattern, int n) {
    string result(n, ' ');
    for (int i = 0; i < n; ++i) result[i] = pattern[i % pattern.size()];
    return result;
}

void emit(const string &s, int x, int y) {
    cout << s.size() << ' ' << x << ' ' << y << '\n' << s << '\n';
}

void maximum(int kind) {
    const int n = N_MAX;
    if (kind == 0) emit(string(n, '9'), 1, 9999);
    else if (kind == 1) emit(string(n, '0'), 1, 1000000000);
    else if (kind == 2) emit(cycle("10", n), 10, 10);
    else emit(cycle("1000000000", n), 1000000000, 1000000000);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1 9\n0\n",
        "1 1 1\n1\n",
        "1 1 8\n9\n",
        "2 10 10\n10\n",
        "3 1 21\n210\n",
        "3 1 100\n010\n",
        "3 10 20\n101\n",
        "2 2 2\n12\n",
        "10 1000000000 1000000000\n1000000000\n",
        "10 1000000000 1000000000\n1000000001\n",
        "5 1 1000000000\n98765\n",
        "6 11 111\n111111\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108402ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    int low = rng.uniform(1, 30);
    const auto digits = word("0123456789", n);
    const auto high = rng.uniform(low, 1000);
    emit(digits, low, high);
}
