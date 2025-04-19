#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

struct FenwickTree {
    int n;
    vector<int> bit;
    FenwickTree(int n) : n(n), bit(n + 1) {}

    void add(int i, int x) {
        for (i++; i <= n; i += i & -i) {
            bit[i] += x;
        }
    }

    int sum(int i) {
        int res = 0;
        for (i++; i > 0; i -= i & -i) {
            res += bit[i];
        }
        return res;
    }
};

int len(int n) {
    return to_string(n).size();
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    string query[] = {"update", "get"};

    int n = gen.uniform(10, 2000);
    int q = gen.uniform(10, 2000);
    printf("%d %d\n", n, q);
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = gen.uniform(0, 1000);
    }
    FenwickTree bit(n + 1);
    for (int i = 1; i <= n; i++) {
        bit.add(i, len(a[i]));
        printf("%d%c", a[i], " \n"[i == n]);
    }
    while (q--) {
        int type = gen.uniform(0, 1);
        if (type == 0) {
            int idx = gen.uniform(1, n);
            int val = gen.uniform(0, 1000);
            printf("%s %d %d\n", query[type].c_str(), idx, val);
            bit.add(idx, len(val) - len(a[idx]));
            a[idx] = val;
        }
        else {
            int u = gen.uniform(1, n);
            int v = gen.uniform(u, n);
            int sum = bit.sum(v) - bit.sum(u - 1);
            printf("%s %d %d %d\n", query[type].c_str(), u, v, gen.uniform(1, sum + 5));
        }
    }
    
    return 0;
}
