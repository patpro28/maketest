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
        int A, B = 0; cin >> A; if (n == 2) cin >> B;
        vector<int> dp((A + 1) * (B + 1)); dp[0] = 1;
        for (int j = 0; j < m; ++j) {
            int b; cin >> b;
            for (int x = A; x >= 0; --x) for (int y = B; y >= 0; --y) {
                int &v = dp[x * (B + 1) + y];
                if (x >= b) { v += dp[(x - b) * (B + 1) + y]; if (v >= MOD) v -= MOD; }
                if (y >= b) { v += dp[x * (B + 1) + y - b]; if (v >= MOD) v -= MOD; }
            }
        }
        cout << dp.back() << '\n';
    }
}
