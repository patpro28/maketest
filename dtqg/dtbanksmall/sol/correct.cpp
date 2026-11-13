#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
const int MOD = 1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<long long> a(n), b(m), sum(1 << m);
        for (auto &x : a) cin >> x;
        for (auto &x : b) cin >> x;
        for (int mask = 1; mask < (1 << m); ++mask) {
            int j = __builtin_ctz((unsigned)mask);
            sum[mask] = sum[mask ^ (1 << j)] + b[j];
        }
        vector<int> dp(1 << m); dp[0] = 1;
        int full = (1 << m) - 1;
        for (long long target : a) {
            vector<int> next(1 << m);
            for (int mask = 0; mask <= full; ++mask) if (dp[mask]) {
                int available = full ^ mask;
                for (int sub = available; sub; sub = (sub - 1) & available) if (sum[sub] == target) {
                    int &v = next[mask | sub]; v += dp[mask]; if (v >= MOD) v -= MOD;
                }
            }
            dp.swap(next);
        }
        int answer = 0;
        for (int v : dp) { answer += v; if (answer >= MOD) answer -= MOD; }
        cout << answer << '\n';
    }
}
