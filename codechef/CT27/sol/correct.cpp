#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) begin(x), end(x)
const int mod = pow(10, 9) + 7;
const int MAX = pow(10, 5) + 1;
const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int mod_pow(int a, int b)
{
    if (a == 0 || a == 1)
        return a;
    if (b == 0)
        return 1;

    int ha = mod_pow(a, b / 2);
    ha *= ha;
    ha %= mod;
    if (b & 1)
        ha *= a;

    return ha % mod;
}
int inv(int a)
{
    return mod_pow(a, mod - 2);
}

int32_t main()
{
    // your code goes here
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    auto solve = [&]() -> void
    {
        int N, M;
        cin >> N >> M;

        unordered_map<int, vector<int>> mp;
        vector<int> A(N), B(M);
        for (int i = 0; i < N; i++)
        {
            cin >> A[i];
            mp[A[i]].push_back(i);
        }
        for (auto &x : B)
            cin >> x;

        A.erase(unique(A.begin(), A.end()), A.end());
        sort(A.begin(), A.end());

        bool can = true;

        int ls = -1;
        int res = 1;

        for (int i = 0; i < M; i++)
        {
            int to = B[i];

            int pos = upper_bound(A.begin(), A.end(), to) - A.begin();

            if (pos == 0)
            {
                can = false;
                break;
            }

            int from = A[pos - 1];
            int del = abs(to - from);

            res += del;
            int k = upper_bound(mp[from].begin(), mp[from].end(), ls) - mp[from].begin();

            if (k == (int) mp[from].size())
            {
                ls = mp[from].front();
                res++;
            }
            else
            {
                ls = mp[from][k];
            }
        }

        if (can)
            cout << res << endl;
        else
            cout << -1 << endl;
    };

    int test = 1;
    cin >> test;
    while (test--)
        solve();

    return 0;
}
