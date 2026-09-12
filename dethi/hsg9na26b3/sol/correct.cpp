#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e3;

int cnt[MAX + 5], n, k;

namespace sub1
{
    int main()
    {
        cout << *max_element(cnt + 1, cnt + MAX + 1) << "\n";
        return 0;
    }
} // namespace sub1

namespace sub2
{
    int ans[2 * MAX + 5];

    int main()
    {
        for (int i = 1; i <= MAX; i++)
        {
            for (int j = i; j <= MAX; j++)
            {
                ans[i + j] += min(cnt[i], cnt[j]) / (i == j ? 2 : 1);
            }
        }
        cout << *max_element(ans + 2, ans + 2 * MAX + 1) << "\n";
        return 0;
    }
} // namespace sub2

namespace sub3 // k = 3
{
    int main()
    {
        int res = 0, x;
        // sum = 3
        res = max(res, cnt[1] / 3);
        // sum = 4
        res = max(res, min(cnt[1] / 2, cnt[2]));
        // sum = 5 = (1,1,3) (1,2,2)
        x = min(cnt[1], cnt[2] / 2);
        res = max(res, x + min((cnt[1] - x) / 2, cnt[3]));
        // sum = 6 = (1,2,3) (2,2,2)
        x = min({cnt[1], cnt[2], cnt[3]});
        res = max(res, x + (cnt[2] - x) / 3);
        // sum = 7 = (1,3,3) (2,2,3)
        x = min(cnt[3], cnt[2] / 2);
        res = max(res, x + min((cnt[3] - x) / 2, cnt[1]));
        // sum = 8 = (2,3,3)
        res = max(res, min(cnt[2], cnt[3] / 2));
        // sum = 9 = (3,3,3)
        res = max(res, cnt[3] / 3);
        cout << res << "\n";
        return 0;
    }
} // namespace sub3

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        int val;
        cin >> val;
        cnt[val]++;
    }
    if (k == 1)
        return sub1::main();
    else if (k == 2)
        return sub2::main();
    else if (k == 3)
        return sub3::main();
    return 0;
}