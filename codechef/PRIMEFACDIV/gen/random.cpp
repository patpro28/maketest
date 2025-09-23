#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;
using ll = long long;
using u128 = __uint128_t;

const long long MAX = 1e18;

ll binpow(ll a, ll b, ll m)
{
    ll res = 1;
    a %= m;
    while (b > 0)
    {
        if (b & 1)
            res = (u128)res * a % m;
        a = (u128)a * a % m;
        b >>= 1;
    }
    return res;
}

bool test(ll a, ll n, ll k, ll m)
{
    ll mod = binpow(a, m, n);
    if (mod == 1 || mod == n - 1)
        return true;
    for (ll i = 0; i + 1 < k; ++i)
    {
        mod = (u128)mod * mod % n;
        if (mod == n - 1)
            return true;
    }
    return false;
}

bool is_prime(ll n)
{
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (count(bases.begin(), bases.end(), n))
        return true;
    if (n < 3e9)
        bases = {2, 3, 5, 7};
    ll k = 0, m = n - 1;
    while (m % 2 == 0)
        k++, m /= 2;
    for (ll &a : bases)
        if (!test(a, n, k, m))
            return false;
    return true;
}

int rand_prime(Random gen)
{
    while (true)
    {
        long long p = gen.uniform<long long>(2, sqrt(MAX));
        if (is_prime(p))
            return p;
    }
}

int main(int, char *argv[])
{

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 100000);
    cout << t << endl;
    for (int i = 0; i < t; ++i)
    {
        long long a = gen.uniform<long long>(1, MAX);
        long long b = gen.uniform<long long>(1, MAX);
        int k = gen.uniform(0, 1);
        if (k == 0)
        {
            cout << a << " " << b << endl;
        }
        else
        {
            vector<ll> primes;
            for (int i = 0; i < 4; ++i)
            {
                ll p = rand_prime(gen);
                primes.push_back(p);
            }
            ll a = 1, b = 1;
            while (true)
            {
                ll p = primes[gen.uniform(0, 3)];
                if (a > MAX / p)
                    break;
                a *= p;
            }
            while (true)
            {
                ll p = primes[gen.uniform(0, 3)];
                if (b > MAX / p)
                    break;
                b *= p;
            }
            cout << a << " " << b << endl;
        }
    }
    return 0;
}
