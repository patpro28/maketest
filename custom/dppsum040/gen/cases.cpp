#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
using ll = long long;
int main(int argc, char **argv) {
    (void)argc;
    const int code = 40;
    int seed = stoi(argv[1]);
    mt19937_64 rng(20261102ULL + 1000 * code + seed);
    int n = seed < 2 ? 1 : seed < 4 ? seed : seed < 16 ? 7 + 5 * seed : 200000;
    int k = seed % 4 == 0 ? 1 : seed % 4 == 1 ? n : seed % 4 == 2 ? max(1, n / 2) : max(1, n - 1);
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        ll x;
        if (seed == 16) x = 0;
        else if (seed == 17) x = code == 38 || code == 39 ? 500000000 : 1000000000;
        else if (seed == 18) x = code == 39 ? 1000000000 : i % 2 ? 999999999 : -1000000000;
        else if (seed == 19) x = (ll)(rng() % 2000000001ULL) - 1000000000;
        else if (seed % 8 == 0) x = 0;
        else if (seed % 8 == 1) x = 1;
        else if (seed % 8 == 2) x = i % 2 ? 3 : 1;
        else if (seed % 8 == 3) x = -1000000000;
        else if (seed % 8 == 4) x = i - n / 2;
        else if (seed % 8 == 5) x = n / 2 - i;
        else if (seed % 8 == 6) x = i % 3 ? 11 : 0;
        else x = (ll)(rng() % 21) - 10;
        a[i] = A_MIN == 0 ? abs(x) : x;
    }
    if (seed == 17 && code == 40) {
        fill(a.begin(), a.end(), 555555555);
        a.back() += 111111;
    }
    ll first = 0;
    for (int i = 0; i < k; ++i) first += a[i];
    cout << n << ' ' << k;
    if (code >= 31 && code <= 33) cout << ' ' << max(-S_MAX, min(S_MAX, first + seed % 3 - 1));
    if (code == 34) cout << ' ' << max(-S_MAX, first - (seed % 2)) << ' ' << min(S_MAX, first + (seed % 2));
    ll m = vector<ll>{1,2,7,1000000000}[seed % 4];
    if (code == 35) cout << ' ' << m;
    if (code == 36) cout << ' ' << m << ' ' << (seed % 3 ? first % m : (first + 1) % m);
    if (code == 38) {
        ll value = first, digits = 0;
        while (value) { digits += value % 10; value /= 10; }
        cout << ' ' << (seed % 4 == 0 ? 0 : seed % 4 == 3 ? 135 : digits);
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) cout << a[i] << (i + 1 == n ? '\n' : ' ');
}
