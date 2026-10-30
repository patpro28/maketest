#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
int main(int argc, char **argv) {
    (void)argc;
    const int code = 30;
    int seed = stoi(argv[1]);
    mt19937_64 rng(20261030ULL + 1000 * code + seed);
    int n = seed < 2 ? 1 : seed < 4 ? seed : seed < 16 ? 7 + seed * 5 : 200000;
    int q = seed >= 16 ? 200000 : 6 + seed * 3;
    int k = code == 23 ? vector<int>{1,2,7,1000000000}[seed % 4]
                       : vector<int>{-1000000000,0,1000000000,3}[seed % 4];
    cout << n << ' ' << q;
    if (code == 23 || code == 25) cout << ' ' << k;
    cout << '\n';
    if (code == 24) {
        string s(n, 'a');
        for (int i = 0; i < n; ++i) {
            if (seed % 4 == 1) s[i] = char('a' + i % 3);
            if (seed % 4 == 2) s[i] = char('a' + (i / 3) % 3);
            if (seed % 4 == 3) s[i] = char('a' + rng() % 3);
        }
        cout << s << '\n';
    } else {
        for (int i = 0; i < n; ++i) {
            long long x;
            if (seed == 16) x = 1000000000;
            else if (seed == 17) x = i - n / 2;
            else if (seed == 18) x = i % 2 ? 999999999 : -1000000000;
            else if (seed == 19) x = (long long)(rng() % 2000000001ULL) - 1000000000;
            else if (seed % 8 == 0) x = 0;
            else if (seed % 8 == 1) x = 7;
            else if (seed % 8 == 2) x = i % 2 ? 1 : -3;
            else if (seed % 8 == 3) x = -1000000000;
            else if (seed % 8 == 4) x = i - n / 2;
            else if (seed % 8 == 5) x = n / 2 - i;
            else if (seed % 8 == 6) x = (i / 3) % 4 - 2;
            else x = (long long)(rng() % 21) - 10;
            if (code == 25 && seed >= 8 && seed < 16) {
                x = (long long)k + i % 3 - 1;
                x = max(A_MIN, min(A_MAX, x));
            }
            cout << x << (i + 1 == n ? '\n' : ' ');
        }
    }
    for (int i = 0; i < q; ++i) {
        int l = 1 + rng() % n, r = 1 + rng() % n;
        if (l > r) swap(l, r);
        if (i % 7 == 0) { l = 1; r = n; }
        if (i % 7 == 1) l = r = n;
        if (i % 7 == 2) l = r = 1;
        if (i % 7 == 3) r = l;
        if (i % 7 == 4) l = 1;
        if (i % 7 == 5 && n > 1) { l = n - 1; r = n; }
        cout << l << ' ' << r << '\n';
    }
}
