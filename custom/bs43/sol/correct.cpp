#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t, l, n, q, i, x, s, a[100005], b[100005], d;
    cin >> t;
    while (t--)
    {
        cin >> l >> n >> q;
        for (i = 1; i <= n; i++)
            cin >> a[i];
        for (i = 1; i <= n; i++)
            cin >> b[i];
        for (int i = 1; i < n; ++i) {
            assert(a[i] < a[i + 1]);
            assert(b[i] < b[i + 1]);
        }
        assert(a[n] == l);
        while (q--)
        {
            cin >> d;
            assert(0 <= d && d <= l);
            x = lower_bound(a + 1, a + 1 + n, d) - a - 1;
            s = b[x] + (d - a[x]) * 1.0 * (b[x + 1] - b[x]) / (a[x + 1] - a[x]);
            cout << s << ' ';
        }
        cout << '\n';
    }
}