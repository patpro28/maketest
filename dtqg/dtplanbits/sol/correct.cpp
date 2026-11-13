#include <bits/stdc++.h>
using namespace std;
const int LEN = 70;
const int BASE = 2;
long long dp[LEN][20][20][1 << 8];
int A[LEN], B[LEN], a[10], b[10], m;
const int MOD = 1e9;

long long cal(int i, int ra, int rb, int mask);

void loop(int i, int j, int ra, int rb, int pmask, int mask, long long &ans) {
    if (i == m) {
        if (ra % BASE == A[j] and rb % BASE == B[j]) {
            ans = (ans + cal(j + 1, ra / BASE, rb / BASE, mask)) % MOD;
        }
        return;
    }
    for (int k = 0; k < BASE; ++k) {
        if (k == 0 || (k == 1 and (pmask >> i & 1) == 0))
            loop(i + 1, j, ra + k * a[i], rb + k * b[i], pmask, mask | (k << i), ans);
    }
}

long long cal(int i, int ra, int rb, int mask) {
    if (i == LEN - 1) return (ra == 0 and rb == 0);
    auto &res = dp[i][ra][rb][mask];
    if (res != -1) return res;
    res = 0;
    loop(0, i, ra, rb, mask, 0, res);
    return res;
}

int main() {
    cin >> m;
    long long inA, inB; cin >> inA >> inB;
    for (int i = 0; i < LEN; ++i) {
        A[i] = inA % BASE; inA /= BASE;
        B[i] = inB % BASE; inB /= BASE;
    }
    for (int i = 0; i < m; ++i) cin >> a[i] >> b[i];
    memset(dp, -1, sizeof dp);
    cout << cal(0, 0, 0, 0);
}