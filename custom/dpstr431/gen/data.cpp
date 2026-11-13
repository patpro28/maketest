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
    if (kind == 0) emit(string(n, '0'), 100, 5000);
    else if (kind == 1) emit(string(n, '1'), 100, 5000);
    else if (kind == 2) emit(string(n, '1'), 1, 5000);
    else emit(cycle("0123456789", n), 100, 1);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1 5000\n0\n",
        "1 1 2\n1\n",
        "1 1 3\n3\n",
        "2 2 7\n00\n",
        "2 1 1\n00\n",
        "4 2 3\n1203\n",
        "4 2 2\n1111\n",
        "4 3 2\n1111\n",
        "3 3 9\n999\n",
        "3 2 9\n909\n",
        "5 1 1\n12345\n",
        "5 5 1\n12345\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108431ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    const auto digits = word("00123369", n);
    const auto parts = rng.uniform(1, min(7, n));
    const auto divisor = rng.uniform(1, 7);
    emit(digits, parts, divisor);
}
