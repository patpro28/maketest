#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
inline void emit(const std::vector<int> &v) {
    for (int i = 0; i < int(v.size()); ++i) printf("%s%d", i ? " " : "", v[i]);
    puts("");
}
inline int generate(int argc, char **argv, int group) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20260913 + 100*group + seed);
    int limit = group == 1 ? 20 : group == 2 ? 200 : group == 3 ? 5000 : 200000;
    int n = seed < 8 ? limit : rnd.uniform(limit/2, limit);
    int k = std::min(n, 100);
    if (seed == 0) k = 1;
    if (seed == 1) k = 2;
    if (seed == 8) k = rnd.uniform(3, std::min(n, 100));
    if (group == 1 && seed == 0) n = 1;
    std::vector<int> a(k), x(n);
    for (int &v : a) v = rnd.uniform(-100,100);
    for (int &v : x) v = rnd.uniform(-1000000000,1000000000);
    if (seed == 1) { std::fill(a.begin(),a.end(),-100); std::fill(x.begin(),x.end(),1000000000); }
    if (seed == 2) std::fill(a.begin(),a.end(),0);
    if (seed == 3) std::fill(x.begin(),x.end(),0);
    if (seed == 4) { std::fill(a.begin(),a.end(),100); std::fill(x.begin(),x.end(),1000000000); }
    if (seed == 5) { std::fill(a.begin(),a.end(),100); std::fill(x.begin(),x.end(),-1000000000); }
    if (seed == 6) {
        for (int i = 0; i < k; ++i) a[i] = i%2 ? -100 : 100;
        for (int i = 0; i < n; ++i) x[i] = i%2 ? 1000000000 : -1000000000;
    }
    if (seed == 7) { for (int &v : a) v = rnd.uniform(-1,1); for (int &v : x) v = rnd.uniform(-2,2); }
    if (seed == 9) { a.front() = -100; a.back() = 100; std::sort(x.begin(),x.end()); }
    if (group == 4) {
        std::vector<int> pool;
        for (int v = -100; v <= 100; ++v) pool.push_back(v);
        for (int i = 200; i > 0; --i) std::swap(pool[i], pool[rnd.uniform(0,i)]);
        for (int i = 0; i < k; ++i) a[i] = pool[i];
    }
    printf("%d %d\n",n,k); emit(a); emit(x);
    return 0;
}
