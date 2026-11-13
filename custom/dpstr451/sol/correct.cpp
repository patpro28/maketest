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
    string s;
    cin >> n >> s;
    const int mod = 1000000007;
    const int stride = n + 1;
    vector<uint16_t> lcp(stride * stride);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            if (s[i] == s[j]) lcp[i * stride + j] = 1 + lcp[(i + 1) * stride + j + 1];
        }
    }
    vector<int> prefix(stride * stride);
    for (int end = 1; end <= n; ++end) {
        for (int len = 1; len <= end; ++len) {
            int start = end - len;
            int ways = 0;
            if (s[start] != '0') {
                if (!start) {
                    ways = 1;
                } else {
                    ways = prefix[start * stride + min(start, len - 1)];
                    if (start >= len) {
                        int same = lcp[(start - len) * stride + start];
                        if (same < len && s[start - len + same] < s[start + same])
                            ways = prefix[start * stride + len];
                    }
                }
            }
            ways += prefix[end * stride + len - 1];
            if (ways >= mod) ways -= mod;
            prefix[end * stride + len] = ways;
        }
    }
    cout << prefix[n * stride + n] << '\n';
}
