#include "random.h"
#include "../params.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void emit(const string &a, const string &b, int k) {
    cout << a.size() << ' ' << b.size() << ' ' << k << '\n' << a << '\n' << b << '\n';
}

void maximum(int kind) {
    const int n = N_MAX;
    const int m = M_MAX;
    string a(n, 'a'), b(m, kind == 0 ? 'b' : 'a');
    if (kind == 2) {
        a.back() = 'b';
        b.back() = 'c';
    }
    if (kind == 3) b.pop_back();
    const int budgets[] = {50, 0, 1, 50};
    if (kind == 3) b.assign(m - 50, 'a');
    emit(a, b, budgets[kind]);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1 0\na\na\n",
        "1 1 0\na\nb\n",
        "1 2 1\na\naa\n",
        "2 1 0\naa\na\n",
        "3 3 0\nabc\nabc\n",
        "2 2 1\nab\nba\n",
        "6 7 3\nkitten\nsitting\n",
        "4 2 2\naaaa\naa\n",
        "3 4 1\nabc\nzabc\n",
        "4 4 2\nxabc\nabcx\n",
        "6 4 2\nabcabc\nbcab\n",
        "4 4 4\naaaa\nbbbb\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108551ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    const int m = rng.uniform(lowSize, highSize);
    string a = word("abc", n);
    string b = word("abc", m);
    const auto budget = rng.uniform(0, 12);
    emit(a, b, budget);
}
