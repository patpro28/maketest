#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
int main(int argc, char **argv) {
    (void)argc;
    const int kind = 0;
    int seed = stoi(argv[1]);
    mt19937_64 rng(20261030ULL + seed);
    int n = seed < 2 ? 1 : seed < 4 ? 2 : seed < 16 ? 7 + seed * 5 : 200000;
    int q = seed >= 16 ? 200000 : 5 + seed * 2;
    int k = kind == 3 ? vector<int>{1, 2, 7, 1000000000}[seed % 4]
                     : vector<int>{0, 81, 1, 10}[seed % 4];
    int u = seed % 4 == 0 ? 0 : seed % 4 == 1 ? -5 : seed % 4 == 2 ? -1000000000 : 999999999;
    int v = seed % 4 == 0 ? 0 : seed % 4 == 1 ? 5 : 1000000000;
    vector<int> good, bad;
    if (kind == 0) { good = {-1000000000, -2, 0, 2, 1000000000}; bad = {-1, 1, 999999999}; }
    if (kind == 1) { good = {1, 1000000000}; bad = {-1, 0, -1000000000}; }
    if (kind == 2) { good = {-1, -1000000000}; bad = {0, 1, 1000000000}; }
    if (kind == 3) { good = {0, k, -k}; bad = k == 1 ? good : vector<int>{1, -1, k - 1}; }
    if (kind == 4) { good = {u, v, (int)(((long long)u + v) / 2)}; bad = u > A_MIN ? vector<int>{(int)A_MIN, u - 1} : v < A_MAX ? vector<int>{v + 1, (int)A_MAX} : good; }
    if (kind == 5) { good = {0, 1, 4, 9, 999950884}; bad = {-1, 2, 999950883, 999950885, 1000000000}; }
    if (kind == 6) { good = {2, 3, 17, 999983}; bad = {0, 1, 4, 25, 999999, 1000000}; }
    if (kind == 7) { good = {0, 7, 11, 121, 1001, 999999999}; bad = {10, 1010, 123, 1000000000}; }
    if (kind == 8) { good = k == 0 ? vector<int>{0} : k == 81 ? vector<int>{999999999} : k == 1 ? vector<int>{1, 10, 1000000000} : vector<int>{19, 28, 55, 91}; bad = k == 0 ? vector<int>{1, 10, 1000000000} : vector<int>{0, 2, 11}; }
    if (kind == 9) { good = {7, 77, 17, 70, 707, 700000007}; bad = {0, 1, 123, 999999999, 1000000000}; }
    cout << n << ' ' << q;
    if (kind == 3 || kind == 8) cout << ' ' << k;
    if (kind == 4) cout << ' ' << u << ' ' << v;
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        int x;
        if (seed == 0 || seed == 16) x = bad[i % bad.size()];
        else if (seed == 1 || seed == 17) x = good[i % good.size()];
        else if (seed % 4 == 2 || seed == 18) x = i % 2 ? good[i % good.size()] : bad[i % bad.size()];
        else if (seed % 4 == 3 && i % 2) x = (int)(A_MIN + (long long)(rng() % (A_MAX - A_MIN + 1)));
        else x = i % 3 ? good[rng() % good.size()] : bad[rng() % bad.size()];
        if (seed == 17) x = kind == 3 ? (1000000000 / k) * k : good.back();
        if (seed == 18 && kind == 4) x = 1000000000;
        cout << x << (i + 1 == n ? '\n' : ' ');
    }
    for (int i = 0; i < q; ++i) {
        int l = 1 + rng() % n, r = 1 + rng() % n;
        if (l > r) swap(l, r);
        if (i % 6 == 0) { l = 1; r = n; }
        if (i % 6 == 1) l = r = n;
        if (i % 6 == 2) l = r = 1;
        if (i % 6 == 3) r = l;
        if (i % 6 == 4) l = 1;
        cout << l << ' ' << r << '\n';
    }
}
