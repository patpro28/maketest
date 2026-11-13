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
    if (kind == 0) emit(cycle("abcdefghijklmnopqrstuvwxyz", n), 1, n);
    else if (kind == 1) emit(string(n, 'a'), 2, n);
    else if (kind == 2) emit(cycle("ab", n), 2, 2);
    else emit(string(n, 'a'), 1, n);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1 1\na\n",
        "2 2 2\naa\n",
        "2 1 2\naa\n",
        "2 1 2\nab\n",
        "3 2 3\naba\n",
        "4 2 2\nabca\n",
        "4 2 3\nabba\n",
        "3 1 1\nabc\n",
        "4 1 4\naaaa\n",
        "8 3 4\nabcddabc\n",
        "6 2 4\nabccde\n",
        "6 4 5\nabcdef\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108432ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    int low = rng.uniform(1, min(n, 4));
    const auto s = word("abcde", n);
    const auto high = rng.uniform(low, n);
    emit(s, low, high);
}
