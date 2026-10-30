#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "fast_io.h"
using namespace std;
using ll = long long;

int main() {
    FastInput in;
    FastOutput out;
    int n, q; string s; in >> n >> q >> s;
    vector<array<int, 26>> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[i] = p[i - 1];
        ++p[i][s[i - 1] - 'a'];
    }
    while (q--) {
        int l, r; char c; in >> l >> r >> c;
        out << p[r][c - 'a'] - p[l - 1][c - 'a'] << '\n';
    }
}
