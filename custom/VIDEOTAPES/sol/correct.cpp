// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
using namespace std;
using ll = long long int;
mt19937_64 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];

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
        int type; cin >> type;
        if (type == 1) {
            ll L, R; cin >> L >> R;
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
            cout << last << '\n';
        }
        else {
            ll pos, val; cin >> pos >> val;
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
}