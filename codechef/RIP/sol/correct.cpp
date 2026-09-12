#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../debug.h"
#else
#define dbg(...) "11-111"
#endif

int32_t main() {
    ios_base::sync_with_stdio(0);   cin.tie(0);

    
    auto __solve_testcase = [&]() -> void {
        int n, m;  cin >> n >> m;
        vector<int> a(n), b(n), c(m), vis(n), compress(1);
        for(auto &i : a)    cin >> i, compress.push_back(i);
        for(auto &i : b)    cin >> i;
        for(auto &i : c)    cin >> i, vis[i - 1] = 1;

        sort(compress.begin(), compress.end());
        compress.resize(unique(compress.begin(), compress.end()) - compress.begin());
        for(auto &i : a)    i = lower_bound(compress.begin(), compress.end(), i) - compress.begin();
        int S = compress.size();
        vector<multiset<int>> upd(S + 1);

        for(int i = 0 ; i < n ; i++) if(!vis[i])
            upd[a[i]].insert(b[i]);

        vector<int> cnt(S + 1);
        int lst = 0;
        long long res = 0;

        for(int &i : c) {
            --i;
            if(a[i] > lst) {
                cnt[a[i]]++;
                upd[a[i]].insert(b[i]);
            } else {
                res += b[i];
            }
            lst = a[i];
        }

        multiset<int> ms;
        int s = 1, rem = 0;
        upd[S - 1].erase(upd[S - 1].begin());

        for(int i = S - 1 ; i >= 0 ; i--) {
            for(auto &u : upd[i])
                ms.insert(u);

            rem += cnt[i];
            while(s < rem) {
                ms.erase(ms.begin());   s++;
            }
        }

        cout << res + accumulate(ms.begin(), ms.end(), 0ll) << '\n';
    };

    // sum (N - L + 1) * L * 2 ^ (N - L + 1) / 2 ^ N
    
    int no_of_tests;   cin >> no_of_tests;
    for(int test_no = 1 ; test_no <= no_of_tests ; test_no++)
        __solve_testcase();
    

    return 0;
}