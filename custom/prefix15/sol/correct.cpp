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
    vector<ll> a(n), p(2 * n + 1);
    for (ll &x : a) in >> x;
    for (int i = 1; i <= 2 * n; ++i) p[i] = p[i - 1] + a[(i - 1) % n];
    while (q--) {
        int l, k; in >> l >> k;
        out << p[l + k - 1] - p[l - 1] << '\n';
    }
}
