// Đếm số lượng số là tích 2 số nguyên tố phân biệt bé hơn hoặc bẳng n (n ≤ 10^6)
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int count = 0;

    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j * j <= i; ++j)
        {
            if (i % j == 0)
            {
                int k = i / j;
                if (j < k and isPrime(k))
                    count++;
                break;
            }
        }
    }

    cout << count << "\n";
    return 0;
}