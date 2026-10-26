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
    long long best[2][3] = {{NEG, NEG, NEG}, {NEG, NEG, NEG}}, total = 0;
    for (int i = 0; i < n; ++i) {
        int t = s[i] - 'a';
        long long one = max(0LL, max(best[1-t][1], best[1-t][2])) + w[i];
        long long two = best[t][1] == NEG ? NEG : best[t][1] + w[i];
        best[t][1] = max(best[t][1], one);
        best[t][2] = max(best[t][2], two); total += w[i];
    }
    long long keep = 0;
    for (int c = 0; c < 2; ++c) for (int k = 1; k <= 2; ++k) keep = max(keep, best[c][k]);
    cout << total - keep << '\n';
}
