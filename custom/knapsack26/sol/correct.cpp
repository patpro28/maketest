#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main()
{
    int n, w;
    scanf("%d%d", &n, &w);
    const long long NEG = -(1LL << 60);
    vector<long long> dp(w + 1, 0);
    for (int i = 0; i < n; ++i)
    {
        int f, c;
        long long v;
        scanf("%d%d%lld", &f, &c, &v);
        auto previous = dp;
        vector<long long> opened(w + 1, NEG);
        for (int s = 0; s <= w; ++s)
        {
            if (s >= f + c)
                opened[s] = max(opened[s], previous[s - f - c] + v);
            if (s >= c && opened[s - c] != NEG)
                opened[s] = max(opened[s], opened[s - c] + v);
            dp[s] = max(previous[s], opened[s]);
        }
    }
    printf("%lld\n", dp[w]);
}
