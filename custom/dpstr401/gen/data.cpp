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

void emit(const string &s) {
    cout << s.size() << "\n" << s << "\n";
}

void maximum(int kind) {
    const int n = N_MAX;
    if (kind == 0) emit(string(n, '1'));
    else if (kind == 1) emit(string(n, '9'));
    else if (kind == 2) emit("1" + string(n - 1, '0'));
    else emit(cycle("10", n));
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1\n0\n",
        "1\n1\n",
        "1\n9\n",
        "2\n06\n",
        "2\n10\n",
        "2\n20\n",
        "2\n30\n",
        "2\n26\n",
        "2\n27\n",
        "3\n101\n",
        "3\n110\n",
        "6\n111111\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108401ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    const auto digits = word("00112269", n);
    emit(digits);
}
