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

void emit(const string &s, int k) {
    cout << s.size() << ' ' << k << '\n' << s << '\n';
}

void maximum(int kind) {
    const int n = N_MAX;
    if (kind == 0) emit(string(n, 'a'), 50);
    else if (kind == 1) emit(cycle("abcdefghijklmnopqrstuvwxyz", n), 26);
    else if (kind == 2) emit(cycle("ab", n), 2);
    else emit(string(n, 'a'), 2);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 50\na\n",
        "2 2\nab\n",
        "2 2\naa\n",
        "3 3\naba\n",
        "5 5\nabcba\n",
        "4 1\naaaa\n",
        "4 50\naaaa\n",
        "5 4\nabbba\n",
        "6 4\nabcabc\n",
        "4 3\nzzzz\n",
        "6 50\nabcdef\n",
        "7 5\nabababa\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108403ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    const auto s = word("abc", n);
    const auto maxLength = rng.uniform(1, min(50, n + 2));
    emit(s, maxLength);
}
