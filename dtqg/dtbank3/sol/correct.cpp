#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
const int MOD = 1000000007;
struct Solver
{
    int n, m;
    vector<long long> a, b;
    vector<int> memo;
    // Projects are processed in a fixed order. Package indices within one
    // project must increase, so each allocation has a unique construction.
    int solve(int mask, int p, int project, long long used)
    {
        if (project == n)
            return 1;
        if (used == a[project])
            return solve(mask, 0, project + 1, 0);
        if (p == m)
            return 0;

        int &ans = memo[mask * m + p];
        if (ans != -1)
            return ans;

        // Không cấp gói p cho công trình hiện tại.
        ans = solve(mask, p + 1, project, used);

        // Cấp gói p cho công trình hiện tại.
        if (!(mask >> p & 1) && used + b[p] <= a[project])
        {
            ans += solve(mask | (1 << p), p + 1, project, used + b[p]);
            if (ans >= MOD)
                ans -= MOD;
        }

        return ans;
    }
    int run()
    {
        if (accumulate(a.begin(), a.end(), 0LL) > accumulate(b.begin(), b.end(), 0LL))
            return 0;
        sort(a.rbegin(), a.rend());
        sort(b.begin(), b.end());
        memo.assign((1 << m) * m, -1);
        return solve(0, 0, 0, 0);
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        Solver s;
        cin >> s.n >> s.m;
        s.a.resize(s.n);
        s.b.resize(s.m);
        for (auto &x : s.a)
            cin >> x;
        for (auto &x : s.b)
            cin >> x;
        cout << s.run() << '\n';
    }
}
