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
    int n;
    long long low, high;
    string s;
    cin >> n >> low >> high >> s;
    vector<int> best(n + 1, n + 1);
    best[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (best[i] > n || s[i] == '0') continue;
        long long value = 0;
        for (int j = i; j < n && j < i + 10; ++j) {
            value = value * 10 + s[j] - '0';
            if (value > high) break;
            if (value >= low) best[j + 1] = min(best[j + 1], best[i] + 1);
        }
    }
    cout << (best[n] <= n ? best[n] : -1) << '\n';
}
