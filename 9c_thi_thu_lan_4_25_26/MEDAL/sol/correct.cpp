#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, m;
    long long K;

    cin >> N >> K >> m;

    vector<long long> a(N);

    for (auto &x : a)
        cin >> x;

    sort(a.begin(), a.end());

    vector<int> len(N);

    int r = 0;

    for (int l = 0; l < N; l++)
    {
        while (r < N && a[r] - a[l] <= K)
            r++;

        len[l] = r - l;
    }

    if (m == 1)
    {
        cout << *max_element(len.begin(), len.end()) << '\n';
        return 0;
    }

    vector<int> suf(N + 1, 0);

    for (int i = N - 1; i >= 0; i--)
    {
        suf[i] = max(suf[i + 1], len[i]);
    }

    int ans = 0;

    for (int i = 0; i < N; i++)
    {
        ans = max(ans, len[i] + suf[i + len[i]]);
    }

    cout << ans << '\n';
}