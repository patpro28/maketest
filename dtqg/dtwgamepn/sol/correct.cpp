#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n, mod; string s; cin >> m >> n >> mod >> s;
    vector<string> g(m); for (auto &row : g) cin >> row;
    if (m > n) {
        vector<string> h(n, string(m, '#'));
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) h[j][i] = g[i][j];
        g.swap(h); swap(m, n);
    }
    int distance = m + n - 2;
    if (int(s.size()) > distance + 1 || g[0][0] == '#' || g[0][0] != g[m-1][n-1]) {
        cout << 0 << '\n'; return 0;
    }
    string rev(s.rbegin(), s.rend());
    // Proper prefixes of S and reverse(S) form the non-accepting states of
    // the two-pattern suffix automaton. A match is an absorbing state.
    vector<string> words(1, "");
    for (const string &pattern : {s, rev}) for (int k = 1; k < int(s.size()); ++k) {
        string w = pattern.substr(0, k);
        if (find(words.begin(), words.end(), w) == words.end()) words.push_back(w);
    }
    int found = int(words.size()), K = found + 1;
    vector<array<int,26>> go(K);
    go[found].fill(found);
    for (int q = 0; q < found; ++q) for (int c = 0; c < 26; ++c) {
        string w = words[q] + char('a' + c);
        if (w.find(s) != string::npos || w.find(rev) != string::npos) { go[q][c] = found; continue; }
        int best = 0;
        for (int j = 1; j < found; ++j) if (words[j].size() > words[best].size() && words[j].size() <= w.size()
            && w.compare(w.size()-words[j].size(), words[j].size(), words[j]) == 0) best = j;
        go[q][c] = best;
    }
    vector<bool> accept(K, false); accept[found] = true;
    for (int q = 0; q < found; ++q) {
        string tail = words[q];
        // An odd-length path shares the middle cell between its halves.
        if (distance % 2 == 0 && !tail.empty()) tail.pop_back();
        reverse(tail.begin(), tail.end());
        accept[q] = (words[q] + tail).find(s) != string::npos;
    }
    auto id = [=](int x, int u, int q) { return (x * m + u) * K + q; };
    vector<int> dp(m * m * K), next(dp.size());
    dp[id(0, m-1, go[0][g[0][0]-'a'])] = 1 % mod;
    for (int t = 0; t < distance / 2; ++t) {
        fill(next.begin(), next.end(), 0);
        for (int x = max(0, t-n+1); x <= min(m-1, t); ++x) {
            int y = t - x;
            for (int u = max(x, distance-t-n+1); u < m; ++u) {
                int v = distance - t - u;
                if (v < y || v >= n) continue;
                for (int q = 0; q < K; ++q) if (int ways = dp[id(x,u,q)]) {
                    for (int down = 0; down < 2; ++down) for (int up = 0; up < 2; ++up) {
                        int nx = x + down, ny = y + 1 - down;
                        int nu = u - up, nv = v - 1 + up;
                        if (nx >= m || ny >= n || nu < nx || nv < ny) continue;
                        char c = g[nx][ny];
                        if (c == '#' || c != g[nu][nv]) continue;
                        int nq = go[q][c-'a'];
                        int &value = next[id(nx,nu,nq)];
                        value += ways; if (value >= mod) value -= mod;
                    }
                }
            }
        }
        dp.swap(next);
    }
    int answer = 0, t = distance / 2;
    for (int x = 0; x < m; ++x) for (int u = x; u < m; ++u) {
        int y = t - x, v = distance - t - u;
        if (y < 0 || y >= n || v < y || v >= n) continue;
        if ((u-x) + (v-y) != distance % 2) continue;
        for (int q = 0; q < K; ++q) if (accept[q]) {
            answer += dp[id(x,u,q)]; if (answer >= mod) answer -= mod;
        }
    }
    cout << answer << '\n';
}
