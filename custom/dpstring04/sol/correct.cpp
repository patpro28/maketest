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
    long long best[3] = {0, 0, 0}; const string colors = "RGB";
    for (int i = 0; i < n; ++i) {
        long long next[3] = {INF, INF, INF};
        for (int c = 0; c < 3; ++c) for (int p = 0; p < 3; ++p) if (c != p)
            next[c] = min(next[c], best[p] + (s[i] == colors[c] ? 0 : w[i]));
        copy(next, next + 3, best);
    }
    cout << *min_element(best, best + 3) << '\n';
}
