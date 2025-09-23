/*
Author: Tu Pham Anh
Date: 2025/06/13 - 22:28
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int N = 5e3 + 1;

bool candidates[N][N];
short a[N][N], mx[N][N];
int s[N][N];
int n, m, k;

int sum(int x, int y) {
    assert(x >= k + 1 && x <= n - k && y >= k + 1 && y <= m - k);
    int x1 = x - k, y1 = y - k;
    int x2 = x + k, y2 = y + k;
    return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        deque<int> dq; // store max value in the window of size 2 * k + 1
        for (int j = 1; j <= m; ++j) {
            while (!dq.empty() && a[i][dq.back()] <= a[i][j]) {
                dq.pop_back();
            }
            dq.push_back(j);
            if (j >= 2 * k + 1) {
                // Check if middle value is equal to the max value
                candidates[i][j - k] = dq.front() == j - k;
                mx[i][j - k] = a[i][dq.front()];
                if (dq.front() == j - 2 * k) {
                    dq.pop_front();
                }
            }
        }
    }

    int ans = 0;

    for (int j = k + 1; j <= m - k; ++j) {
        deque<int> dq;
        for (int i = 1; i <= n; ++i) {
            while (!dq.empty() && mx[dq.back()][j] <= mx[i][j]) {
                dq.pop_back();
            }
            dq.push_back(i);
            if (i >= 2 * k + 1) {
                if (dq.front() == i - k and candidates[i - k][j]) {
                    ans = max(ans, sum(i - k, j));
                }
                if (dq.front() == i - 2 * k) {
                    dq.pop_front();
                }
            }
        }
    }

    cout << ans;

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}