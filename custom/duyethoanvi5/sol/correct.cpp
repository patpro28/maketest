#include <bits/stdc++.h>
using namespace std;

int x[21], used[21], pos[21];
bool found = false;

void dq(int i, int n) {
    if (i == n + 1) {
        found = true;
        for (int j = 1; j <= n; ++j)
            cout << x[j] << ' ';
        cout << '\n';
        return;
    }
    if (pos[i]) dq(i + 1, n);
    else
        for (int j = 1; j <= n; ++j) {
            if (!used[j]) {
                used[j] = 1;
                x[i] = j;
                dq(i + 1, n);
                used[j] = 0;
            }
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n, k; cin >> n >> k;
    if (!(n >= 3 && n <= 20 && k >= 1 && k <= n)) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 1; i <= k; ++i) {
        int u, v; cin >> u >> v;
        if (!(u >= 1 && u <= n && v >= 1 && v <= n)) {
            cout << 0 << '\n';
            return 0;
        }
        x[u] = v;
        if (used[v] || pos[u]) {
            cout << 0 << '\n';
            return 0;
        }
        used[v] = 1;
        pos[u] = 1;
    }

    dq(1, n);
    if (!found) cout << 0 << '\n';

    return 0;
}
