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
    // Longest suffix equal to a proper prefix of "aba": "", "a", "ab".
    const int go[3][2] = {{1, 0}, {1, 2}, {-1, 0}};
    long long best[3] = {0, INF, INF};
    for (int i = 0; i < n; ++i) {
        long long next[3] = {INF, INF, INF}; int c = s[i] - 'a';
        for (int p = 0; p < 3; ++p) if (best[p] != INF) {
            next[p] = min(next[p], best[p] + w[i]);
            int q = go[p][c]; if (q != -1) next[q] = min(next[q], best[p]);
        }
        copy(next, next + 3, best);
    }
    cout << *min_element(best, best + 3) << '\n';
}
