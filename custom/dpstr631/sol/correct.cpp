#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n >> s;
    vector<long long> cost(n), f(n);
    for (long long &x : cost)
        cin >> x;
    for (int l = n - 1; l >= 0; --l)
    {
        long long inside = 0;
        for (int r = l + 1; r < n; ++r)
        {
            long long old = f[r];
            long long best = min(cost[l] + f[r], cost[r] + f[r - 1]);
            if (s[l] == s[r])
                best = min(best, inside);
            f[r] = best;
            inside = old;
        }
    }
    cout << f[n - 1] << '\n';
}
