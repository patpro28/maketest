#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAXN = 150;
const int ALPHABET = 26;

const int dx[] = {0, 1, -1, 0};
const int dy[] = {1, 0, 0, -1};

int n, m, mod;
int nxt[ALPHABET][ALPHABET], nxt1[ALPHABET][ALPHABET];
int dp[MAXN + 5][MAXN + 5][MAXN + 5][22][2];
string s;
char grid[MAXN + 5][MAXN + 5];

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int f(int x1, int y1, int x2, int y2, int k1, int k2) {
    if (grid[x1][y1] != grid[x2][y2]) return 0;

    int nk1 = nxt[k1][grid[x1][y1] - 'a'];
    int nk2 = nxt1[k2][grid[x2][y2] - 'a'];

    if (abs(x1 - x2) + abs(y1 - y2) <= 1) {
        string comb = s.substr(0, nk1) + s.substr(s.size() - nk2, nk2);
        if (x1 == x2 && y1 == y2 && nk1 && nk2) {
            comb = s.substr(0, nk1) + s.substr(s.size() - k2, k2);
        }
        if (comb.find(s) != string::npos) return 1;
        return (nk1 == s.size() || nk2 == s.size());
    }

    if (dp[x1][y1][x2][max(k1, k2)][k1 < k2] != -1) return dp[x1][y1][x2][max(k1, k2)][k1 < k2];

    int tot = 0;
    for (int i = 0; i <= 1; ++i) {
        for (int j = 2; j <= 3; ++j) {
            int nx1 = x1 + dx[i], ny1 = y1 + dy[i];
            int nx2 = x2 + dx[j], ny2 = y2 + dy[j];
            if (nx1 <= nx2 && ny1 <= ny2 && grid[nx1][ny1] != '#' && grid[nx2][ny2] != '#') {
                add(tot, f(nx1, ny1, nx2, ny2, nk1, nk2));
            }
        }
    }
    return dp[x1][y1][x2][max(k1, k2)][k1 < k2] = tot;
}

void solve() {
    cin >> n >> m >> mod >> s;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
        }
    }

    memset(dp, -1, sizeof dp);

    for (int i = 0; i <= s.size(); ++i) {
        for (int j = 0; j < ALPHABET; ++j) {
            if (i == s.size()) {
                nxt[i][j] = nxt1[i][j] = s.size();
                continue;
            } else {
                string cur = s.substr(0, i) + char('a' + j);
                while (cur.size()) {
                    if (s.substr(0, cur.size()) == cur) {
                        nxt[i][j] = cur.size();
                        break;
                    }
                    cur.erase(cur.begin());
                }
                if (cur.empty()) nxt[i][j] = 0;

                cur = char('a' + j) + s.substr(s.size() - i, i);
                while (cur.size()) {
                    if (s.substr(s.size() - cur.size(), cur.size()) == cur) {
                        nxt1[i][j] = cur.size();
                        break;
                    }
                    cur.pop_back();
                }
                if (cur.empty()) nxt1[i][j] = 0;
            }
        }
    }

    cout << f(1, 1, n, m, 0, 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    while (t--) solve();
    return 0;
}
