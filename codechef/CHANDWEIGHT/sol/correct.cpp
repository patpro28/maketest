
#include <bits/stdc++.h>

using namespace std;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases;
    cin >> test_cases;
    for (int i = 0; i < test_cases; i++)
    {
        int n;
        cin >> n;
        vector<long long> arr(n), brr(n);
        for (auto &a : arr)
        {
            cin >> a;
        }
        for (auto &b : brr)
        {
            cin >> b;
        }
        vector<long long> prefix(n, 0), suffix(n, 0);
        for (int i = 0; i < n; ++i)
        {
            prefix[i] += (brr[i] - arr[i]);
            if (i && prefix[i - 1] > brr[i])
            {
                prefix[i] += (prefix[i - 1] - brr[i]);
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            suffix[i] += (brr[i] - arr[i]);
            if (i + 1 < n && suffix[i + 1] > brr[i])
            {
                suffix[i] += (suffix[i + 1] - brr[i]);
            }
        }
        for (int i = 0; i < n; ++i)
        {
            long long needExtra = 0;
            if (i + 1 < n)
                needExtra += suffix[i + 1];
            if (i)
                needExtra += prefix[i - 1];
            long long addedHere = brr[i] - arr[i];
            if (needExtra > brr[i])
                addedHere += (needExtra - brr[i]);
            cout << addedHere << ' ';
        }
        cout << "\n";
    }

    return 0;
}