#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
typedef set<string> ss;
typedef vector<int> vs;
typedef map<int, char> msi;
typedef pair<int, int> pa;
typedef long long int ll;

ll n, q, i, a[300005], cnt[300005], k;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> q;
        for (i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a + n);
        for (i = 0; i < n; i++)
        {
            cnt[i] = (n - i - 1) * (n - i - 2) / 2;
            if (i > 0)
                cnt[i] += cnt[i - 1];
        }
        while (q--)
        {
            cin >> k;
            cout << a[lower_bound(cnt, cnt + n, k) - cnt] << "\n";
        }
    }

    return 0;
}