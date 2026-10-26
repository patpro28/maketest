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
    long long best[2] = {0, 0};
    for (int i = 0; i < n; ++i) {
        int t = string("aeiou").find(s[i]) != string::npos;
        best[t] = max(best[t], best[1-t] + w[i]);
    }
    cout << max(best[0], best[1]) << '\n';
}
