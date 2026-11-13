#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

using ull = unsigned long long;
vector<int> primes;
ull bell(int m)
{
    vector<ull> row(1, 1);
    for (int i = 1; i <= m; ++i)
    {
        vector<ull> next(i + 1);
        next[0] = row.back();
        for (int j = 1; j <= i; ++j)
            next[j] = next[j - 1] + row[j - 1];
        row = next;
    }
    return row[0];
}
ull partitions(int m, int k)
{
    if (k == 1)
        return bell(m) - 1;
    const int small[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    vector<ull> divisors(1, 1);
    for (int i = 0; i < m; ++i)
    {
        int size = divisors.size();
        ull power = 1;
        for (int e = 1; e <= k; ++e)
        {
            power *= small[i];
            for (int j = 0; j < size; ++j)
                divisors.push_back(divisors[j] * power);
        }
    }
    sort(divisors.begin(), divisors.end());
    int d = divisors.size();
    unordered_map<ull, int> index;
    index.reserve(d * 2);
    for (int i = 0; i < d; ++i)
        index[divisors[i]] = i;
    vector<ull> dp(d);
    dp[0] = 1;
    for (int factor = 1; factor < d - 1; ++factor)
        for (int target = factor; target < d; ++target)
            if (divisors[target] % divisors[factor] == 0)
                dp[target] += dp[index[divisors[target] / divisors[factor]]];
    return dp.back();
}
int main()
{
    if (FILE *input = fopen("factor.INP", "r"))
    {
        fclose(input);
        freopen("factor.INP", "r", stdin);
        freopen("factor.OUT", "w", stdout);
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<bool> composite(1000001);
    for (int i = 2; i <= 1000000; ++i)
        if (!composite[i])
        {
            primes.push_back(i);
            if (1LL * i * i <= 1000000)
                for (int j = i * i; j <= 1000000; j += i)
                    composite[j] = true;
        }
    int T;
    cin >> T;
    map<pair<int, int>, ull> cache;
    while (T--)
    {
        ull N;
        cin >> N;
        int m = 0, k = 0;
        for (int p : primes)
        {
            if (ull(p) * p > N)
                break;
            if (N % p)
                continue;
            int exponent = 0;
            do
            {
                N /= p;
                ++exponent;
            } while (N % p == 0);
            ++m;
            k = exponent;
        }
        if (N > 1)
        {
            ++m;
            k = 1;
        }
        auto key = make_pair(m, k);
        if (!cache.count(key))
            cache[key] = partitions(m, k);
        cout << cache[key] << '\n';
    }
}
