#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n, m; long long a; cin >> n >> m >> a;
        vector<long long> b(m), sum(1 << m);
        for (auto &x : b) cin >> x;
        int answer = 0;
        for (int mask = 1; mask < (1 << m); ++mask) {
            int j = __builtin_ctz((unsigned)mask);
            sum[mask] = sum[mask ^ (1 << j)] + b[j];
            if (sum[mask] == a) ++answer;
        }
        cout << answer << '\n';
    }
}
