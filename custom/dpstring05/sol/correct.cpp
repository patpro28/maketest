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
    long long x, y; cin >> n >> x >> y >> s;
    long long best[2] = {0, 0};
    for (int i = 0; i < n; ++i) {
        long long next[2] = {INF, INF};
        for (int c = 0; c < 2; ++c) if (s[i] == '?' || s[i] == 'A' + c) {
            if (i == 0) next[c] = 0;
            else for (int p = 0; p < 2; ++p) if (best[p] != INF)
                next[c] = min(next[c], best[p] + (p == c ? 0 : p == 0 ? x : y));
        }
        copy(next, next + 2, best);
    }
    cout << min(best[0], best[1]) << '\n';
}
