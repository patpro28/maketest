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
    // Color 4 is a sentinel for positions before the beginning.
    long long best[5][5];
    for (auto &row : best) fill(row, row + 5, INF);
    best[4][4] = 0;
    for (int i = 0; i < n; ++i) {
        long long next[5][5];
        for (auto &row : next) fill(row, row + 5, INF);
        for (int a = 0; a < 5; ++a) for (int b = 0; b < 5; ++b) if (best[a][b] != INF)
            for (int c = 0; c < 4; ++c) if (c != a && c != b)
                next[b][c] = min(next[b][c], best[a][b] + (s[i] == 'A' + c ? 0 : w[i]));
        for (int a = 0; a < 5; ++a) copy(next[a], next[a] + 5, best[a]);
    }
    long long answer = INF;
    for (auto &row : best) answer = min(answer, *min_element(row, row + 5));
    cout << answer << '\n';
}
