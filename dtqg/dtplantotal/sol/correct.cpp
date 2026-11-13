#include <bits/stdc++.h>
using namespace std;
const int LEN = 70;
const int BASE = 2;
long long dp[LEN][20][20][20];
int A[LEN], B[LEN], C[LEN], a[10], b[10], m;
const int MOD = 1e9;

long long cal(int i, int ra, int rb, int rc);

void loop(int i, int j, int ra, int rb, int rc, long long &ans) {
    if (i == m) {
        if (ra % BASE == A[j] and rb % BASE == B[j] and rc % BASE == C[j]) {
            ans = (ans + cal(j + 1, ra / BASE, rb / BASE, rc / BASE)) % MOD;
        }
        return;
    }
    for (int k = 0; k < BASE; ++k) {
        loop(i + 1, j, ra + k * a[i], rb + k * b[i], rc + k, ans);
    }
}

long long cal(int i, int ra, int rb, int rc) {
    if (i == LEN - 1) return (ra == 0 and rb == 0 and rc == 0);
    auto &res = dp[i][ra][rb][rc];
    if (res != -1) return res;
    res = 0;
    loop(0, i, ra, rb, rc, res);
    return res;
}

int main() {
    cin >> m;
    long long inA, inB, inC; cin >> inA >> inB >> inC;
    for (int i = 0; i < LEN; ++i) {
        A[i] = inA % BASE; inA /= BASE;
        B[i] = inB % BASE; inB /= BASE;
        C[i] = inC % BASE; inC /= BASE;
    }
    for (int i = 0; i < m; ++i) cin >> a[i] >> b[i];
    memset(dp, -1, sizeof dp);
    cout << cal(0, 0, 0, 0);
}