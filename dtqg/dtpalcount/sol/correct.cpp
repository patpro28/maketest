#include<bits/stdc++.h>
using namespace std;
using ll = long long;

template<int BASE, int MOD>
struct Hash {
    vector<ll> pw, h1, h2;
    ll sz;
    explicit Hash(const string &s) : sz(s.size()) {
        pw.resize(sz + 1, 0);
        h1.resize(sz + 2, 0);
        h2.resize(sz + 2, 0);
        pw[0] = 1;
        for (int i = 1; i <= sz; ++i) {
            pw[i] = pw[i - 1] * BASE % MOD;
            h1[i] = (h1[i - 1] * BASE + s[i - 1] - 'a' + 1) % MOD;
        }
        for (int i = sz; i >= 1; --i) {
            h2[i] = (h2[i + 1] * BASE + s[i - 1] - 'a' + 1) % MOD;
        }
    }

    ll getHash(int l, int r) {
        return (h1[r] - pw[r - l + 1] * h1[l - 1] % MOD + MOD) % MOD;
    }

    ll getHash2(int l, int r) {
        return (h2[l] - pw[r - l + 1] * h2[r + 1] % MOD + MOD) % MOD;
    }

    ll isPalin(int l, int r) {
        return getHash(l, r) == getHash2(l, r);
    }
};

bool minimize(int &a, int b) {
    if (a > b) return a = b, true;
    return false;
}

int l[3], c[3];
int dp[21][21][21], tr[21][21][21];
int nxt[100005][3];

int main() {
    string s; cin >> s;
    Hash<31, 1000000007> h(s);
    int n = s.size();
    int d; cin >> d;
    for (int i = 0; i < d; ++i) cin >> l[i] >> c[i];
    int last[3] = {n + 1, n + 1, n + 1};
    for (int i = n + 2; i > 0; --i)
        for (int j = 0; j < d; ++j) {
            if (i + l[j] - 1 <= n and h.isPalin(i, i + l[j] - 1))
                last[j] = i + l[j] - 1;
            nxt[i][j] = last[j];
        }

    memset(dp, 0x3f, sizeof dp);
    dp[0][0][0] = 0;
    for (int i = 0; i <= c[0]; ++i)
        for (int j = 0; j <= c[1]; ++j)
            for (int k = 0; k <= c[2]; ++k) {
                int cur = dp[i][j][k];
                if (i < c[0] and minimize(dp[i + 1][j][k], nxt[cur + 1][0]))
                    tr[i + 1][j][k] = 0;
                if (j < c[1] and minimize(dp[i][j + 1][k], nxt[cur + 1][1]))
                    tr[i][j + 1][k] = 1;
                if (k < c[2] and minimize(dp[i][j][k + 1], nxt[cur + 1][2]))
                    tr[i][j][k + 1] = 2;
            }

    if (dp[c[0]][c[1]][c[2]] > n) cout << "NO\n";
    else {
        cout << "YES\n";
        int x = c[0], y = c[1], z = c[2];
        deque<pair<int, int>> ans;
        while (x > 0 || y > 0 || z > 0) {
            int R = dp[x][y][z], t = tr[x][y][z];
            int L = R - l[t] + 1;
            ans.push_front({L, R});
            if (t == 0) x--;
            if (t == 1) y--;
            if (t == 2) z--;
        }
        for (auto &[L, R]: ans) cout << L << ' ' << R << '\n';
    }
}