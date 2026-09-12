#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        long long A, B;
        cin >> A >> B;

        if (A == B)
        {
            cout << -1 << '\n';
            continue;
        }

        long long d = llabs(A - B);
        long long cnt = 0;
        for (long long i = 1; i * i <= d; ++i)
        {
            if (d % i == 0)
            {
                cnt++; // i
                if (i * i != d)
                    cnt++; // d / i
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}