#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ll long long
#define mod 1000000007
long long power(long long a, long long b, long long m)
{
    long long p = a, Answer = 1;
    for (long long i = 0; i < 60; i++)
    {
        long long wari = (1LL << i);
        if ((b / wari) % 2 == 1)
        {
            Answer = (Answer * p) % m;
        }
        p = (p * p) % m;
    }
    return Answer;
}
long long Division(long long a, long long b, long long m)
{
    return (a * power(b, m - 2, m)) % m;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    ll N;
    cin >> N;
    if (N == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    ll keta = to_string(N).size();
    ll K = power(10, keta, mod);
    ll NK = 1;
    NK *= N;
    NK %= mod;
    ll kk = (power(K, N, mod) - 1) % mod;
    if (kk < 0)
        kk += mod;
    NK *= kk;
    NK %= mod;
    K %= mod;
    if (K < 0)
        K += mod;
    cout << Division(NK, K - 1, mod);
}