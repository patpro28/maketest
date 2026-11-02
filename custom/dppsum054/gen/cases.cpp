#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"
using namespace std;
int main(int argc, char **argv) {
    (void)argc;
    const int code = 54;
    int seed = stoi(argv[1]);
    mt19937_64 rng(20261102ULL + seed);
    int n = seed < 2 ? 1 : seed < 4 ? seed : seed < 16 ? 7 + seed * 5 : 200000;
    int k = seed % 4 == 0 ? 1 : seed % 4 == 1 ? n : seed % 4 == 2 ? max(1,n/2) : max(1,n-1);
    if (seed == 5 || seed == 13 || seed == 19) k = 1;
    int divisor = vector<int>{1,2,7,1000000000}[seed % 4];
    int u = seed % 4 == 0 ? 0 : seed % 4 == 1 ? -5 : seed % 4 == 2 ? -1000000000 : 999999999;
    int v = seed % 4 == 0 ? 0 : seed % 4 == 1 ? 5 : 1000000000;
    vector<int> good,bad;
    if (code == 51) { good = {-1000000000,-2,0,2,1000000000}; bad = {-1,1,999999999}; }
    if (code == 52) { good = {1,1000000000}; bad = {-1000000000,-1,0}; }
    if (code == 53) { good = {-1,-1000000000}; bad = {0,1,1000000000}; }
    if (code == 54) { good = {0,divisor,-divisor}; bad = divisor == 1 ? good : vector<int>{1,-1,divisor-1}; }
    if (code == 55) { good = {u,v,(int)(((long long)u+v)/2)}; bad = u > A_MIN ? vector<int>{(int)A_MIN,u-1} : v < A_MAX ? vector<int>{v+1,(int)A_MAX} : good; }
    if (code == 56) { good = {0,1,4,9,999950884}; bad = {-1,2,999950883,999950885,1000000000}; }
    if (code == 57) { good = {2,3,17,999983}; bad = {0,1,4,25,999999,1000000}; }
    if (code == 58) { good = {0,7,11,121,1001,999999999}; bad = {10,1010,123,1000000000}; }
    if (code == 59) { good = {7,77,17,70,707,700000007}; bad = {0,1,123,999999999,1000000000}; }
    cout << n << ' ' << k;
    if (code == 54) cout << ' ' << divisor;
    if (code == 55) cout << ' ' << u << ' ' << v;
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        bool marked;
        if (seed == 0 || seed == 3 || seed == 8 || seed == 16) marked = false;
        else if (seed == 1 || seed == 9 || seed == 17) marked = true;
        else if (seed == 4 || seed == 13) marked = i == 0;
        else if (seed == 5 || seed == 12) marked = i == n - 1;
        else if (seed == 2 || seed == 10 || seed == 18) marked = i % 2;
        else if (seed == 6) marked = (i / 3) % 2;
        else if (seed == 7 || seed == 15) marked = i >= n / 2;
        else marked = rng() % 2;
        int x = marked ? good[rng()%good.size()] : bad[rng()%bad.size()];
        if (seed == 19 && i % 3 == 0) x = (int)(A_MIN + (long long)(rng() % (A_MAX - A_MIN + 1)));
        cout << x << (i + 1 == n ? '\n' : ' ');
    }
}
