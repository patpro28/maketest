#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    string s;
    cin >> n >> k >> s;
    vector<vector<int>> cost(n, vector<int>(n));
    for (int left = n - 1; left >= 0; --left) {
        for (int right = left + 1; right < n; ++right) {
            int inner = right - left > 1 ? cost[left + 1][right - 1] : 0;
            cost[left][right] = inner + (s[left] != s[right]);
        }
    }
    const int inf = n + 1;
    vector<int> previous(n + 1, inf), current(n + 1, inf);
    previous[0] = 0;
    for (int parts = 1; parts <= k; ++parts) {
        fill(current.begin(), current.end(), inf);
        for (int end = parts; end <= n; ++end) {
            for (int cut = parts - 1; cut < end; ++cut)
                current[end] = min(current[end], previous[cut] + cost[cut][end - 1]);
        }
        previous.swap(current);
    }
    cout << previous[n] << '\n';
}
