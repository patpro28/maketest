/*
Author: Tu Pham Anh
Date: 2026/08/03 - 18:05
*/
#include <bits/stdc++.h>

using namespace std;

struct HS {
    string ten;
    int toan, tin;
};

HS a[100005];

bool cmp(HS a, HS b) {
    if (a.toan + a.tin != b.toan + b.tin) return a.toan + a.tin > b.toan + b.tin;
    if (abs(a.toan - a.tin) != abs(b.toan - b.tin)) return abs(a.toan - a.tin) < abs(b.toan - b.tin);
    if (a.toan != b.toan) return a.toan > b.toan;
    if (a.ten.size() != b.ten.size()) return a.ten.size() < b.ten.size();
    return a.ten < b.ten;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].ten >> a[i].toan >> a[i].tin;
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        cout << a[i].ten << " " << a[i].toan << " "<< a[i].tin << "\n";
    }

    for (int i = 1; i <= sqrt(n); ++i)
        for (int j = i * i; j <= n; j += i)
            d[j] += 1 + (i * i != j);

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}