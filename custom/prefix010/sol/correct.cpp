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
    int n, q; in >> n >> q;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll x; in >> x;
        p[i] = p[i - 1] + (x % 2 == 0);
    }
    while (q--) {
        int l, r; in >> l >> r;
        out << p[r] - p[l - 1] << '\n';
    }
}
