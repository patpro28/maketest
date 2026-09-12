#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

const int MAXP = 100000;

vector<long long> special[100];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<bool> isPrime(MAXP + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= MAXP; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= MAXP; j += i)
                isPrime[j] = false;
        }
    }

    for (long long p = 2; p <= MAXP; p++)
    {
        if (isPrime[p])
        {
            long long x = p * p;
            special[x % 100].push_back(x);
        }
    }

    int T;
    cin >> T;

    while (T--)
    {
        long long L, R;
        int k;
        cin >> L >> R >> k;

        auto &v = special[k];

        long long ans =
            upper_bound(v.begin(), v.end(), R) -
            lower_bound(v.begin(), v.end(), L);

        cout << ans << '\n';
    }
}