#include "random.h"
#include "../params.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void emit(const string &a, const string &b, long long r, const vector<long long> &d, const vector<long long> &ins) {
    cout << a.size() << ' ' << b.size() << '\n' << a << '\n' << b << '\n' << r << '\n';
    for (int i = 0; i < int(d.size()); ++i) cout << d[i] << (i + 1 == int(d.size()) ? '\n' : ' ');
    for (int j = 0; j < int(ins.size()); ++j) cout << ins[j] << (j + 1 == int(ins.size()) ? '\n' : ' ');
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
    if (kind == 2) {
        emit(a, b, 7, vector<long long>(n, 3), vector<long long>(b.size(), 2));
    } else {
        vector<long long> deletion(n, 1000000000);
        if (kind == 3) deletion.back() = 0;
        emit(a, b, 1000000000, deletion, vector<long long>(b.size(), 1000000000));
    }
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1\na\na\n0\n0\n0\n",
        "1 1\na\nb\n1\n1\n0\n",
        "1 2\na\naa\n2\n2\n0 3\n",
        "2 1\naa\na\n3\n3 4\n0\n",
        "3 3\nabc\nabc\n4\n4 5 6\n0 3 6\n",
        "2 2\nab\nba\n0\n5 6\n0 3\n",
        "6 7\nkitten\nsitting\n1\n6 7 8 9 10 11\n0 3 6 9 12 15 18\n",
        "4 2\naaaa\naa\n2\n7 8 9 10\n0 3\n",
        "3 4\nabc\nzabc\n3\n8 9 10\n0 3 6 9\n",
        "4 4\nxabc\nabcx\n4\n9 10 11 12\n0 3 6 9\n",
        "6 4\nabcabc\nbcab\n0\n10 11 12 13 14 15\n0 3 6 9\n",
        "4 4\naaaa\nbbbb\n1\n11 12 13 14\n0 3 6 9\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108531ULL + seed);
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
    vector<long long> deletion(n), insertion(m);
    for (auto &cost : deletion) cost = rng.uniform(0, 9);
    for (auto &cost : insertion) cost = rng.uniform(0, 9);
    const auto replacement = rng.uniform(0, 12);
    emit(a, b, replacement, deletion, insertion);
}
