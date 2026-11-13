#include "random.h"
#include "../params.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void emit(const string &a, const string &b) {
    cout << a.size() << ' ' << b.size() << '\n' << a << '\n' << b << '\n';
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
    if (kind == 2) b.back() = '?';
    if (kind == 3) b.assign(m - 1, '?');
    emit(a, b);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1\na\n?\n",
        "1 1\na\nb\n",
        "1 2\na\na?\n",
        "2 1\naa\n?\n",
        "3 3\nabc\nab?\n",
        "2 2\nab\nb?\n",
        "6 7\nkitten\n?it?in?\n",
        "4 2\naaaa\naa\n",
        "3 4\nabc\nz?bc\n",
        "4 4\nxabc\n?bc?\n",
        "6 4\nabcabc\nbc?b\n",
        "4 4\naaaa\nb?bb\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108530ULL + seed);
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
    const auto pattern = word("abc??", m);
    emit(a, pattern);
}
