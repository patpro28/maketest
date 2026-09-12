#include <iostream>
using namespace std;

int n, a[26];
long long diff = 1e18, cnt = 0;

void np(int i, long long s1, long long s2)
{
    if (i == n + 1)
    {
        long long ndiff = abs(s1 - s2);
        if (ndiff < diff)
            diff = ndiff, cnt = 1;
        else if (ndiff == diff)
            cnt++;
        return;
    }
    np(i + 1, s1 + a[i], s2);
    np(i + 1, s1, s2 + a[i]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    np(2, a[1], 0);
    cout << diff << ' ' << cnt << '\n';
}