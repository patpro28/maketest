#include "random.h"
#include "../params.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void emit(const string &a, const string &b, long long x, long long y, long long z) {
    cout << a.size() << ' ' << b.size() << '\n' << a << '\n' << b << '\n';
    cout << x << ' ' << y << ' ' << z << '\n';
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
    if (kind == 0) emit(a, b, 1000000000, 1000000000, 1000000000);
    else if (kind == 1) emit(a, b, 2, 0, 5);
    else if (kind == 2) emit(a, b, 1, 1, 9);
    else emit(a, b, 5, 3, 9);
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1\na\na\n0 0 0\n",
        "1 1\na\nb\n2 3 9\n",
        "1 2\na\naa\n8 0 7\n",
        "2 1\naa\na\n8 1 7\n",
        "3 3\nabc\nabc\n1000000000 1000000000 1000000000\n",
        "2 2\nab\nba\n9 9 1\n",
        "6 7\nkitten\nsitting\n0 0 0\n",
        "4 2\naaaa\naa\n2 3 9\n",
        "3 4\nabc\nzabc\n8 0 7\n",
        "4 4\nxabc\nabcx\n8 1 7\n",
        "6 4\nabcabc\nbcab\n1000000000 1000000000 1000000000\n",
        "4 4\naaaa\nbbbb\n9 9 1\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108550ULL + seed);
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
    const long long prices[] = {0, 1, 5, 1000000000};
    const auto opening = prices[rng.uniform(0, 3)];
    const auto extension = prices[rng.uniform(0, 3)];
    const auto replacement = prices[rng.uniform(0, 3)];
    emit(a, b, opening, extension, replacement);
}
