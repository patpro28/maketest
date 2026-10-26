#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const long long INF = 1LL << 60, NEG = -INF;
    (void) INF; (void) NEG;
    int n; string s;
    cin >> n >> s;
    vector<long long> w(n); for (auto &v : w) cin >> v;
    vector<long long> best(26, 0);
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        int t = s[i] - 'a'; long long previous = 0;
        for (int c = 0; c < 26; ++c) if (c != t) previous = max(previous, best[c]);
        best[t] = max(best[t], previous + w[i]); total += w[i];
    }
    cout << total - *max_element(best.begin(), best.end()) << '\n';
}
