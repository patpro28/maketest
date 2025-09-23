/*
Author: Tu Pham Anh
Date: 2025/07/18 - 17:55
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> pos(3, -1);
        string ans(n, ' ');
        for (int i = n - 1; i >= 0; --i)
        {
            int k = s[i] == 'R' ? 0 : s[i] == 'P' ? 1
                                                  : 2;
            if (pos[(k + 1) % 3] == -1)
                ans[i] = s[i];
            else
                ans[i] = ans[pos[(k + 1) % 3]];
            pos[k] = i;
        }
        cout << ans << '\n';
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}