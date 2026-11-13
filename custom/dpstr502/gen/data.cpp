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

void emit(const string &a, const string &b) {
    cout << a.size() << '\n' << a << '\n' << b << '\n';
}

void maximum(int kind) {
    const int n = N_MAX;
    if (kind == 0) emit(cycle("ab", n), cycle("ba", n));
    else if (kind == 1) emit(string(n, 'a'), string(n, 'a'));
    else if (kind == 2) emit(string(n, 'a'), string(n, 'b'));
    else emit(cycle("ab", n), string(n, 'c'));
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1\na\na\n",
        "1\na\nb\n",
        "2\nab\nba\n",
        "2\nab\nab\n",
        "2\naa\naa\n",
        "3\nabc\nbca\n",
        "3\nabc\nbaz\n",
        "4\nabab\nbaba\n",
        "4\nabcd\nbadc\n",
        "3\naab\naba\n",
        "4\naabb\nabab\n",
        "4\nabca\nbaac\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108502ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    const auto a = word("abc", n);
    const auto b = word("abc", n);
    emit(a, b);
}
