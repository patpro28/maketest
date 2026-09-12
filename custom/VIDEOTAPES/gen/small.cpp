#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;
using ll = int;

int cnt = 0;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 100);
    int q = gen.uniform<int>(1, 100);

    vector<int> a(n), b(n);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        a[i] = gen.uniform<int>(1, 100);
        b[i] = gen.uniform<int>(1, n);
        cout << a[i] << " " << b[i] << "\n";
    }
    const int B = 400;
    /**
     * Divide into blocks of size B
     * let prev[i] = index of largest j < i such that b[i] = b[j]
     * in each block, keep elements sorted by prev[i] and build prefix sums
     * updates:
     * - changing value just changes the prefix sum within a block
     * - changing color changes the ordering and prefix sum of at most two blocks
     * query:
     * - for a full block, some prefix sum (find using binary search)
     * - for a non-full block, brute
     */
    
    vector<int> jump(n, -1);
    vector<set<int>> who(n+1);
    for (int i = 0; i < n; ++i) {
        if (!who[b[i]].empty()) jump[i] = *who[b[i]].rbegin();
        who[b[i]].insert(i);
    }
    
    vector<int> block_order(n);
    vector<ll> pref(n);
    auto recalc = [&] (int block) {
        cnt++;
        int lo = block*B, hi = min(n, block*B + B);
        for (int i = lo; i < hi; ++i) block_order[i] = i;
        sort(begin(block_order)+lo, begin(block_order)+hi, [&] (int i, int j) {
            return jump[i] < jump[j];
        });
        for (int i = lo; i < hi; ++i) {
            int u = block_order[i];
            pref[i] = a[u];
            if (i > lo) pref[i] += pref[i-1];
        }
    };
    for (int i = 0; i <= n/B; ++i) recalc(i);
    ll last = 0;
    while (q--) {
        int type;
        type = gen.uniform<int>(1, 3);
        if (type == 1) {
            int L = gen.uniform<int>(1, n);
            int R = gen.uniform<int>(L, n);
            L ^= last, R ^= last;
            cout << type << " " << L << " " << R << "\n";
            L ^= last, R ^= last;
            --L, --R;
            last = 0;
            int low = L;
            while (L <= R) {
                if (L%B == 0) break;
                if (jump[L] < low) last += a[L];
                ++L;
            }
            while (L <= R) {
                if (R%B == B-1) break;
                if (jump[R] < low) last += a[R];
                --R;
            }

            if (L <= R) {
                for (int block = L/B; block <= R/B; ++block) {
                    int lo = block*B, hi = block*B + B;
                    auto till = lower_bound(begin(block_order)+lo, begin(block_order)+hi, low, [&] (int i, int x) {
                        return jump[i] < x;
                    }) - begin(block_order);
                    if (till > lo) last += pref[till-1];
                }
            }
            // cout << last << '\n';
        }
        else {
            int pos = gen.uniform<int>(1, n);
            int val = gen.uniform<int>(1, 100);
            if (type == 3) val = gen.uniform<int>(1, n);
            pos ^= last, val ^= last;
            cout << type << " " << pos << " " << val << "\n";
            pos ^= last, val ^= last;
            --pos;

            if (type == 2) {
                a[pos] = val;
                recalc(pos/B);
            }
            else {
                auto it = who[b[pos]].find(pos);
                int x = n, y = n;
                if (next(it) != end(who[b[pos]])) {
                    x = *next(it);
                    jump[x] = jump[pos];
                }
                who[b[pos]].erase(pos);
                
                who[val].insert(pos);
                b[pos] = val;
                auto it2 = who[val].find(pos);
                if (next(it2) != end(who[val])) {
                    y = *next(it2);
                    jump[y] = pos;
                }
                if (it2 == begin(who[val])) jump[pos] = -1;
                else jump[pos] = *prev(it2);
                
                if (x > y) swap(x, y);
                recalc(pos/B);
                if (x != n and pos/B < x/B) recalc(x/B);
                if (y != n and x/B < y/B) recalc(y/B);
            }
        }
    }

    return 0;
}
