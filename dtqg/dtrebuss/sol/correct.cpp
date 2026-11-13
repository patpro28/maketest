/*
Author: Tu Pham Anh
Date: 2026/11/04 - 16:07
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int dp[N][2];
array<int, 3> tr[N][2];
string A, B, C;

int cal(int i, int c) {
    if (i == 0) return c == 0;
    auto &res = dp[i][c];
    if (res != -1) return res;
    res = 0;
    int lowA = (A[i - 1] == '*') ? 0 : (A[i - 1] == '#' ? 1 : A[i - 1] - '0');
    int lowB = (B[i - 1] == '*') ? 0 : (B[i - 1] == '#' ? 1 : B[i - 1] - '0');
    int highA = isdigit(A[i - 1]) ? A[i - 1] - '0' : 9;
    int highB = isdigit(B[i - 1]) ? B[i - 1] - '0' : 9;
    for (int a = lowA; a <= highA; ++a) {
        for (int b = lowB; b <= highB; ++b) {
            int sum = a + b + c;
            bool valid = false;
            if (isdigit(C[i - 1]) and sum % 10 == C[i - 1] - '0') valid = true;
            if (C[i - 1] == '#' and sum % 10 >= 1) valid = true;
            if (C[i - 1] == '*') valid = true;
            if (valid and cal(i - 1, sum / 10)) {
                res = 1;
                tr[i][c] = {a, b, sum % 10};
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> A >> B >> C;
    int n = A.size(), m = B.size();
    if (A[0] == '*') A[0] = '#';
    if (B[0] == '*') B[0] = '#';
    if (C[0] == '*') C[0] = '#';
    if (max(A.size(), B.size()) > C.size()) {
        cout << "No Solution\n";
        return 0;
    }
    int L = C.size();
    while (A.size() < L) A = '0' + A;
    while (B.size() < L) B = '0' + B;
    memset(dp, -1, sizeof dp);
    if (cal(L, 0)) {
        string resA, resB, resC;
        int carry = 0;
        for (int i = L; i >= 1; --i) {
            auto [a, b, c] = tr[i][carry];
            resA += (char)(a + '0');
            resB += (char)(b + '0');
            resC += (char)(c + '0');
        }
        reverse(resA.begin(), resA.end());
        reverse(resB.begin(), resB.end());
        reverse(resC.begin(), resC.end());
        cout << resA.substr(L - n, n) << "\n" << resB.substr(L - m, m) << "\n" << resC << "\n";
    } else {
        cout << "No Solution\n";        
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}