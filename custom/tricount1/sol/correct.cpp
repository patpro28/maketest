#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int> A(n);
    for (int &x : A)
    {
        cin >> x;
    }

    if (n == 1)
    {
        cout << "0\n";
        return;
    }

    int ans = 0;
    sort(A.begin(), A.end());

    int start = A[n - 1] - A[n - 2] + 1;
    int end = A[n - 1] + A[n - 2] - 1;
    ans += end - start + 1;

    int prev = start;
    for (int i = n - 2; i > 0; i--)
    {
        int diff = A[i] - A[i - 1] + 1;
        int sum = A[i] + A[i - 1] - 1;

        if (diff < prev)
        {
            if (sum < prev)
            {
                ans += (sum - diff + 1);
            }
            else
            {
                ans += (min(prev, sum) - diff);
            }
        }
        prev = min(prev, diff);
    }

    cout << ans << endl;
}

int32_t main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
