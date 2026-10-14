#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"

inline void emit(const std::vector<int>& a) {
    for (int i = 0; i < int(a.size()); ++i) printf("%s%d", i ? " " : "", a[i]);
    puts("");
}
inline int generate(int argc, char **argv, int group) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20260913 + group * 100 + seed);
    int t = (group == 0 || seed < 2) ? 20 : 4;
    printf("%d\n", t);
    for (int tc = 0; tc < t; ++tc) {
        int n = group == 0 ? rnd.uniform(1, 5) : group == 2 ? rnd.uniform(6, 1000) : rnd.uniform(1001, 100000);
        if (group == 0 && seed == 0) n = tc < 4 ? 1 : tc < 12 ? 2 : 5;
        if (group != 0 && (seed < 2 || tc == 0)) n = group == 2 ? 1000 : 100000;
        std::vector<int> u(n-1), v(n-1), w(n);
        int mode = (seed + tc) % 10;
        for (auto a : {&u, &v, &w}) for (int &x : *a) {
            x = rnd.uniform(1, 10000);
            if (mode == 0) x = 1; // Odd trees, even cycles.
            if (mode == 1) x = 10000;
            if (mode == 2) x = 9999;
            if (mode == 3) x = rnd.uniform(1, 3);
            if (mode == 4) x = 2 * rnd.uniform(1, 5000);
            if (mode == 5) x = 2 * rnd.uniform(1, 5000) - 1;
            if (mode == 6) x = a == &w ? 10000 : 1;
            if (mode == 7) x = a == &w ? 1 : 10000;
            if (mode == 8) x = rnd.uniform(0, 1) ? 1 : 10000;
            if (mode == 9) x = a == &u ? 9999 : 2;
            if (group == 1) x = (x + 1) / 2 * 2;
        }
        if (group == 0 && seed == 0 && tc < 4) w[0] = tc == 0 ? 1 : tc == 1 ? 2 : tc == 2 ? 9999 : 10000;
        printf("%d\n", n);
        emit(u); emit(v); emit(w);
    }
    return 0;
}
