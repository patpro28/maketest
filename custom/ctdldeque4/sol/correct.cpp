#include <bits/stdc++.h>
#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define N 1000000

using namespace std;
int n, k, a[N + 1];

int main()
{

    fast;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    deque<int> dq;

    for (int i = 1; i <= n; i++)
    {
        while (!dq.empty() && dq.front() < i - k + 1)
            dq.pop_front();

        while (!dq.empty() && a[dq.back()] > a[i])
            dq.pop_back();

        dq.push_back(i);

        if (i >= k)
        {
            cout << a[dq.front()] << '\n';
        }
    }
}