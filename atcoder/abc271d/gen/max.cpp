#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "random.h"
using namespace std;
int main(int, char* argv[]) {
    int seed=atoi(argv[1]);
    Random rng(seed);
    int n=100, s=0;
    vector<pair<int,int>> a(n);
    for (int i=0; i<n; ++i) {
        auto& [x,y]=a[i];
        if (seed<=1) x=y=100;
        else if (seed<=3) x=y=1;
        else if (seed<=5) { x=99; y=100; }
        else if (seed<=7) { x=1; y=100; }
        else if (seed==8) { x=2*rng.uniform(1,50); y=2*rng.uniform(1,50); }
        else { x=rng.uniform(1,100); y=rng.uniform(1,100); }
        s += rng.uniform_bool() ? x : y;
    }
    if (seed==1) s=9999;
    if (seed==3) s=1;
    if (seed==4) s=9950;
    if (seed==5) s=9899;
    if (seed==6) s=5050;
    if (seed==7) s=5000;
    if (seed==8) s=5001;
    if (seed==10) s=10000;
    if (seed==11) s=1;
    cout << n << ' ' << s << '\n';
    for (auto [x,y] : a) cout << x << ' ' << y << '\n';
}
