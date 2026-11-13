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
    if (kind == 0) emit(string(n, 'a'), 100);
    else if (kind == 1) emit(string(n - 1, 'a') + 'b', 1);
    else if (kind == 2) emit(cycle("ab", n), 1);
    else emit(cycle("ab", n), 100);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1\na\n",
        "2 1\nab\n",
        "2 2\nab\n",
        "3 1\naba\n",
        "3 2\naba\n",
        "4 2\nabba\n",
        "4 2\nabcd\n",
        "5 1\naabaa\n",
        "4 3\naaaa\n",
        "6 2\nababab\n",
        "4 3\nzxyz\n",
        "6 1\nabcabc\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108450ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    const auto s = word("abc", n);
    const auto parts = rng.uniform(1, min(n, 8));
    emit(s, parts);
}
