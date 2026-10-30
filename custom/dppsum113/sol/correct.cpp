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
    vector<ll> p(n + 1), w(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll x; in >> x;
        p[i] = p[i - 1] + x;
        w[i] = w[i - 1] + i * x;
    }
    while (q--) {
        int l, r; in >> l >> r;
        out << w[r] - w[l - 1] - (l - 1LL) * (p[r] - p[l - 1]) << '\n';
    }
}
