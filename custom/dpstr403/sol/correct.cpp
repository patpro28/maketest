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
    vector<int> ways(n + 1);
    ways[0] = 1;
    for (int end = 1; end <= n; ++end) {
        for (int start = max(0, end - k); start < end; ++start) {
            if (s[start] != s[end - 1]) continue;
            ways[end] += ways[start];
            if (ways[end] >= 1000000007) ways[end] -= 1000000007;
        }
    }
    cout << ways[n] << '\n';
}
