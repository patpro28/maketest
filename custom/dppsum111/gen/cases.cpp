#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
using ll = long long;
int main(int argc, char **argv) {
    (void)argc;
    int seed = stoi(argv[1]);
    const int kind = 11;
    mt19937_64 rng(20261023ULL + seed);
    int n = seed < 4 ? 1 + seed : seed < 16 ? 10 + seed * 7 : 200000;
    if (kind == 19) n = max(n, 3);
    int m = 0;
    if (kind == 14) {
        n = seed >= 16 ? 700 : seed == 14 ? 1 : seed == 15 ? 700 : 1 + seed;
        m = seed >= 16 ? 700 : seed == 14 ? 700 : seed == 15 ? 1 : 1 + seed % 7;
    }
    int q = seed >= 16 ? 200000 : 6 + seed * 3;
    cout << n;
    if (kind == 14) cout << ' ' << m;
    if (kind != 19) cout << ' ' << q;
    cout << '\n';
    auto value = [&](int i) -> ll {
        int mode = seed % 8;
        ll x = mode == 0 ? 0 : mode == 1 ? A_MAX : mode == 2 ? (i % 2 ? A_MAX : -A_MAX)
             : mode == 3 ? -A_MAX : mode == 4 ? i % 7 - 3 : mode == 5 ? (i == 0 ? A_MAX : 0)
             : mode == 6 ? (i == n - 1 ? -A_MAX : 0)
             : (ll)(rng() % (2 * A_MAX + 1)) - A_MAX;
        if (seed == 19) x = (ll)(rng() % (2 * A_MAX + 1)) - A_MAX;
        return kind == 18 ? abs(x) : x;
    };
    if (kind == 12 || kind == 17) {
        string s(n, 'a');
        for (int i = 0; i < n; ++i) {
            if (seed % 4 == 1) s[i] = char('a' + i % 26);
            else if (seed % 4 == 2) s[i] = char('a' + (i / 3) % 2);
            else if (seed % 4 == 3) s[i] = char('a' + rng() % 26);
        }
        cout << s << '\n';
    } else if (kind == 14) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cout << value(i * m + j) << (j + 1 == m ? '\n' : ' ');
        }
    } else {
        for (int i = 0; i < n; ++i) cout << value(i) << (i + 1 == n ? '\n' : ' ');
    }
    if (kind == 19) return 0;
    for (int t = 0; t < q; ++t) {
        int l = 1 + rng() % n, r = 1 + rng() % n;
        if (l > r) swap(l, r);
        if (t % 6 == 0) { l = 1; r = n; }
        if (t % 6 == 1) r = l;
        if (t % 6 == 2) l = 1;
        if (t % 6 == 3) r = n;
        if (t % 6 == 4) l = r = n;
        if (kind == 14) {
            int y1 = 1 + rng() % m, y2 = 1 + rng() % m;
            if (y1 > y2) swap(y1, y2);
            if (t % 6 == 0) { y1 = 1; y2 = m; }
            if (t % 6 == 1 || t % 6 == 4) y2 = y1;
            cout << l << ' ' << y1 << ' ' << r << ' ' << y2 << '\n';
        } else if (kind == 15) {
            int start = t % 2 ? n : l;
            int length = t % 3 == 0 ? n : t % 3 == 1 ? 1 : 1 + rng() % n;
            cout << start << ' ' << length << '\n';
        } else {
            if (kind == 16 && t % 2) swap(l, r);
            cout << l << ' ' << r;
            if (kind == 12) cout << ' ' << char('a' + t % 26);
            cout << '\n';
        }
    }
}
