/*
Author: Tu Pham Anh
Date: 2025/07/19 - 10:55
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

vector<int> palin;

void initPalin()
{
    for (int i = 0; i < (1 << 15); ++i)
    {
        string s = to_string(i);
        string p = s;
        reverse(p.begin(), p.end());
        if (s == p)
            palin.push_back(i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    initPalin();
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        long long ans = 0;
        for (auto &z : palin)
        {
            vector<int> cnt(1 << 15, 0);
            for (auto &x : a)
            {
                cnt[x]++;
                ans += cnt[x ^ z];
            }
        }
        cout << ans << '\n';
    }

    return 0;
}