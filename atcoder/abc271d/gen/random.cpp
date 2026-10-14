#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "random.h"
using namespace std;
int main(int, char* argv[]) {
    int seed = atoi(argv[1]);
    Random rng(seed);
    int n = rng.uniform(1, seed < 12 ? 12 : 100), s = 0;
    vector<pair<int,int>> a(n);
    for (auto& [x,y] : a) {
        x=rng.uniform(1,100); y=rng.uniform(1,100);
        if (seed%4 == 2) { x=2*rng.uniform(1,50); y=2*rng.uniform(1,50); }
        s += rng.uniform_bool() ? x : y;
    }
    if (seed%4 == 1) s=rng.uniform(1,10000);
    if (seed%4 == 2) s = s == 10000 ? 9999 : s+1;
    cout << n << ' ' << s << '\n';
    for (auto [x,y] : a) cout << x << ' ' << y << '\n';
}
