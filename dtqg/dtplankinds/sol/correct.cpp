#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9;
const int N = 155;
const int K = 22;

int m, A, B, k;
int dp[K][N][N];
int positive[K][N][N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> A >> B >> k;

    dp[0][0][0] = 1;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;

        memset(positive, 0, sizeof(positive));

        for (int used = 1; used <= k; used++) {
            for (int p = a; p <= A; p++) {
                for (int q = b; q <= B; q++) {
                    positive[used][p][q] =
                        (dp[used - 1][p - a][q - b]
                        + positive[used][p - a][q - b]) % MOD;
                }
            }
        }

        for (int used = 0; used <= k; used++) {
            for (int p = 0; p <= A; p++) {
                for (int q = 0; q <= B; q++) {
                    dp[used][p][q] =
                        (dp[used][p][q] + positive[used][p][q]) % MOD;
                }
            }
        }
    }

    cout << dp[k][A][B];

    return 0;
}