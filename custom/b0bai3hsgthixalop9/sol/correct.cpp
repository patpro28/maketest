#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long C;
    cin >> N >> C;

    vector<long long> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    int l = 0, r = N - 1;
    long long ans = 0;

    while (l < r)
    {
        long long sum = a[l] + a[r];
        if (sum <= C)
        {
            ans = max(ans, sum);
            l++; // thử tăng tổng
        }
        else
        {
            r--; // tổng quá lớn
        }
    }

    cout << ans;
    return 0;
}
