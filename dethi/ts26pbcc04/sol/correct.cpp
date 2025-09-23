/*
Author: Tu Pham Anh
Date: 2025/06/05 - 09:05
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif
#define endl '\n'

using namespace std;

namespace A
{
    long long cal(long long l, long long r, int d) {
        long long sd = l / 100 * 100 + d;
        if (sd < l) sd += 100;
        long long sc = r / 100 * 100 + d;
        if (sc > r) sc -= 100;
        return sc / 100 - sd / 100 + 1;
    }

    int main() {
        #define task "funny"
        if (fopen(task".inp", "r")) {
            freopen(task".inp", "r", stdin);
            freopen(task".out", "w", stdout);
        }
        #undef task
        int t, k; cin >> t >> k;
        while (t--) {
            long long a, b;
            cin >> a >> b;
            long long ans = 0;
            for (int d = 0; d < 100; d += k)
                ans += cal(a, b, d);
            cout << ans << '\n';
        }
        return 0;
    }
}

namespace B
{
    const int d = 3 * 97;
    string s;
    int cnt[d];
    int main() {
        #define task "lucky"
        if (fopen(task".inp", "r")) {
            freopen(task".inp", "r", stdin);
            freopen(task".out", "w", stdout);
        }
        #undef task
        cin >> s;
        // Count number of substrings that are divisible by d
        long long ans = 0, sum = 0, pw = 1;
        cnt[0] = 1;
        reverse(s.begin(), s.end());
        for (auto &c : s) {
            int x = c - '0';
            sum = (sum + x * pw) % d;
            ans += cnt[sum];
            cnt[sum]++;
            pw = pw * 10 % d;
        }
        cout << ans << '\n';
        return 0;
    }
}

namespace C
{
    long long cal(vector<int> &a, int k) {
        // Find longest subarray with sum <= k
        int n = a.size();
        int sum = 0, ans = 0;
        for (int l = 0, r = 0; r < n; ++r) {
            sum += a[r];
            while (sum > k)
                sum -= a[l++];
            ans = max(ans, r - l + 1);
        }
        return ans;
    }

    int main() {
        #define task "plan"
        if (fopen(task".inp", "r")) {
            freopen(task".inp", "r", stdin);
            freopen(task".out", "w", stdout);
        }
        #undef task
        int k; cin >> k;
        string s; cin >> s;
        vector<int> a(s.size());
        long long ans = 0;
        for (char c = 'a'; c <= 'z'; ++c) {
            for (int i = 0; i < (int) s.size(); ++i)
                a[i] = abs(s[i] - c);
            ans = max(ans, cal(a, k));
        }
        cout << ans << '\n';
        return 0;
    }
}

namespace D
{   
    using ll = long long;
    const int MOD = 1e9 + 7;
    pair<ll, ll> combine(pair<ll, ll> a, pair<ll, ll> b) {
        if (a.first == b.first)
            return {a.first, (a.second + b.second) % MOD};
        if (a.first > b.first)
            return a;
        return b;
    }

    const int N = 1e5 + 5;
    const int K = 101;
    pair<ll, ll> dp[N][K];
    long long a[N], w[K];

    int main() {
        #define task "invp"
        if (fopen(task".inp", "r")) {
            freopen(task".inp", "r", stdin);
            freopen(task".out", "w", stdout);
        }
        #undef task
        int n, k; cin >> n >> k;
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= k; ++i)
            cin >> w[i];
        dp[0][0] = {0, 1};
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = {0, 1};
            for (int j = 1; j <= k; ++j) {
                pair<ll, ll> tmp = dp[i - 1][j - 1];
                tmp.first += a[i] * w[j];
                dp[i][j] = combine(dp[i - 1][j], tmp);
            }
        }
        cout << dp[n][k].first % MOD << '\n' << dp[n][k].second % MOD << '\n';
        return 0;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    // A::main();
    // B::main();
    // C::main();
    // D::main();

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}