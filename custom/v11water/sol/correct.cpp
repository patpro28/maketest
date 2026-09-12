#include <iostream>
#include <algorithm>
#define fr(a, b, c) for (a = b; a <= c; a++)
#define frr(a, b, c) for (a = b; a >= c; a--)
#define maxn 100100
using namespace std;

int n, a[maxn], l[maxn], r[maxn];
long long re = 0;

int main()
{
    int i, x;
    cin >> n;
    fr(i, 1, n) scanf("%d", &a[i]);
    fr(i, 2, n) l[i] = max(l[i - 1], a[i - 1]);
    frr(i, n - 1, 1) r[i] = max(r[i + 1], a[i + 1]);
    fr(i, 1, n)
    {
        x = min(l[i], r[i]);
        if (x > a[i])
            re += x - a[i];
    }
    cout << re << endl;
    return 0;
}
