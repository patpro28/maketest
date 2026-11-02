#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
using ll = long long;
int main(int argc, char **argv) {
    (void)argc;
    int seed = stoi(argv[1]);
    mt19937_64 rng(20261102ULL + seed);
    int n = seed < 2 ? 1 : seed < 4 ? seed : seed < 16 ? 7 + seed * 5 : 200000;
    int k = seed % 4 == 0 ? 1 : seed % 4 == 1 ? n : seed % 4 == 2 ? max(1, n / 2) : max(1, n - 1);
    if (seed == 16) k = n / 2;
    if (seed == 19) k = 1;
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; ++i) {
        ll x;
        if (seed == 0) x = 0;
        else if (seed == 1) x = -3;
        else if (seed == 16) x = -1000000000;
        else if (seed == 17) x = 1000000000;
        else if (seed == 18) x = i % 2 ? 1000000000 : -1000000000;
        else if (seed == 19) x = (ll)(rng() % 2000000001ULL) - 1000000000;
        else if (seed == 14) x = i == n - 1 ? 1000000000 : 0;
        else if (seed == 15) x = i == n - 1 ? -1000000000 : 0;
        else if (seed % 8 == 0) x = -7;
        else if (seed % 8 == 1) x = 7;
        else if (seed % 8 == 2) x = i % 2 ? 1 : -1;
        else if (seed % 8 == 3) x = i - n / 2;
        else if (seed % 8 == 4) x = n / 2 - i;
        else if (seed % 8 == 5) x = i == 0 ? 1000000000 : -1;
        else if (seed % 8 == 6) x = (i / 3) % 3 - 1;
        else x = (ll)(rng() % 21) - 10;
        cout << x << (i + 1 == n ? '\n' : ' ');
    }
}
