/*
Author: Tu Pham Anh
Date: 2026/10/30 - 10:21
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 101;

// Hàm kiểm tra số chính phương
bool scp(long long n) {
    long long k = sqrtl(n);
    return k * k == n;
}

// Hàm trả về số đảo ngược
long long daonguoc(long long n) {
    long long m = 0;
    while (n > 0) {
        m = m * 10 + n % 10;
        n /= 10;
    }
    return m;
}

// Hàm kiểm tra số đối xứng
bool doixung(long long n) {
    return n == daonguoc(n);
}

// Hàm kiểm tra số chứa 7
bool has7(long long n) {
    while (n > 0) {
        if (n % 10 == 7) return true;
        n /= 10;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    // freopen("DT.INP", "r", stdin);
    // freopen("DT.OUT", "w", stdout);
    
    int t; cin >> t;
    cin >> n; m = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j], m += a[i][j];

    if (t == 1) sub1();
    else sub2();

    return 0;
}