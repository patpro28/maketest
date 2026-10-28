#include <iostream>
#include <vector>
#include "slope.h"
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> l(n), r(n), u(n), v(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
    for (int i = 0; i + 1 < n; ++i) cin >> u[i] >> v[i];
    Slope f;
    for (int i = 0; i < n; ++i) {
        if (i) f.window(u[i - 1], v[i - 1]);
        f.add_left(l[i]); f.add_right(r[i]);
    }
    cout << f.minimum << '\n';
}
