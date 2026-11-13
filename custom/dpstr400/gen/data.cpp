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
    if (kind == 0) emit(string(n, 'a'));
    else if (kind == 1) emit(string(n, 'b'));
    else if (kind == 2) emit(string(n - 1, 'b'));
    else emit(cycle("ab", n));
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1\na\n",
        "1\nb\n",
        "2\naa\n",
        "2\nab\n",
        "2\nba\n",
        "2\nbb\n",
        "3\nbab\n",
        "4\nbbbb\n",
        "5\nbbbbb\n",
        "5\naabaa\n",
        "4\naaab\n",
        "5\nabbaa\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108400ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    const auto s = word("ab", n);
    emit(s);
}
