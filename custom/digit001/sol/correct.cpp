/*
Author: Tu Pham Anh
Date: 2025/03/21 - 20:10
*/
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
int dp[82][82][11][2][2];

int solve(int i, int r1, int r2, int ok1, int ok2, int &K, string &A, string &B) {
    // Nếu đã chạm neo thì trả về điều kiện bài toán
    if (i == A.size()) return (r1 == 0 && r2 == 0);
    // Nếu đã tính rồi thì trả về kết quả luôn
    if (dp[r1][r2][i][ok1][ok2] != -1) return dp[r1][r2][i][ok1][ok2];
    int &res = dp[r1][r2][i][ok1][ok2];
    res = 0;
    int low = ok1 ? A[i] - '0' : 0;
    int high = ok2 ? B[i] - '0' : 9;
    for (int d = low; d <= high; ++d) {
        // Nếu d = N[i] và ok = 1 thì ok tiếp tục = 1, còn không thì ok = 0
        res += solve(i + 1, (r1 * 10 + d) % K, (r2 + d) % K, ok1 && (d == low), ok2 && (d == high), K, A, B);
    }
    return res;
}

int cal(int A, int B, int K) {
    string N = to_string(A);
    string M = to_string(B);
    while (N.size() < M.size()) N = '0' + N;
    memset(dp, -1, sizeof(dp));
    return solve(0, 0, 0, 1, 1, K, N, M);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int A, B, K;
        cin >> A >> B >> K;
        int ans = 0;
        if (K < 82) ans = cal(A, B, K);
        cout << "Case " << i << ": " << ans << '\n';
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}