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
    vector<ll> p(n + 1);
    ll previous = 0;
    for (int i = 1; i <= n; ++i) {
        ll h; in >> h;
        if (i > 1) p[i] = p[i - 1] + abs(h - previous);
        previous = h;
    }
    while (q--) {
        int l, r; in >> l >> r;
        out << abs(p[r] - p[l]) << '\n';
    }
}
