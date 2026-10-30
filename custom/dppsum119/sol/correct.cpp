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
    int n; in >> n;
    vector<ll> a(n);
    ll total = 0;
    for (ll &x : a) { in >> x; total += x; }
    if (total % 3 != 0) { out << 0 << '\n'; return 0; }
    ll target = total / 3, prefix = 0, count = 0, answer = 0;
    for (int j = 0; j < n - 1; ++j) {
        prefix += a[j];
        if (prefix == 2 * target) answer += count;
        if (prefix == target) ++count;
    }
    out << answer << '\n';
}
