#include <bits/stdc++.h>
#define ll long long
#define faster                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
using namespace std;

int n, a, k;
vector<int> p, m, u;

void phantich(int n)
{
    int x = 2;
    int t = 0;
    a = 1;
    while (x * x <= n)
    {
        t = 0;
        while (n % x == 0)
        {
            t++;
            n /= x;
        }
        if (t > 0)
        {
            a *= x;
            p.push_back(x);
            m.push_back(t);
        }
        x++;
    }
    if (n > 1)
    {
        p.push_back(n);
        m.push_back(1);
        a *= n;
    }
    k = p.size();
}

void sol()
{
    for (int x = 1; x * a <= n; x++)
    {
        vector<int> y(k, 0);
        int z = x;
        bool ok = true;
        for (int j = 0; j < k; j++)
        {
            while (z % p[j] == 0)
            {
                y[j]++;
                z /= p[j];
            }
            if ((y[j] + 1) * a * x < m[j])
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            cout << a * x;
            break;
        }
    }
}

int main()
{
    faster
    cin >> n;
    phantich(n);
    sol();
    return 0;
}