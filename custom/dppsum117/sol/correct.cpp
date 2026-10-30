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
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) p[i] = p[i - 1] + (s[i - 1] != s[i - 2]);
    while (q--) {
        int l, r; in >> l >> r;
        out << 1 + p[r] - p[l] << '\n';
    }
}
