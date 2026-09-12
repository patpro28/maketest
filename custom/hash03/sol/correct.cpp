/*
Author: Tu Pham Anh
Date: 2025/11/09 - 21:21
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

// Create KMP to find number of occurrences of pattern in text
int kmp(const string &s, const string &t)
{
    int n = (int)s.size();
    int m = (int)t.size();
    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m;)
    {
        if (t[i] == t[len])
        {
            lps[i++] = ++len;
        }
        else
        {
            if (len)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i++] = 0;
            }
        }
    }
    int cnt = 0;
    for (int i = 0, j = 0; i < n;)
    {
        if (s[i] == t[j])
        {
            i++, j++;
        }
        else
        {
            if (j)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
        if (j == m)
        {
            cnt++;
            j = lps[j - 1];
        }
    }
    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string a, b;
    cin >> a >> b;
    cout << kmp(b, a) << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}