#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long K;
    cin >> N >> K;

    unordered_map<long long, long long> freq;

    long long ans = 0;

    for (int i = 0; i < N; i++)
    {
        long long x;
        cin >> x;

        ans += freq[x - K];
        ans += freq[x + K];

        freq[x]++;
    }

    cout << ans;

    return 0;
}