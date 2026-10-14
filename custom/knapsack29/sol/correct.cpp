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
    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for (int &v : a)
        scanf("%d", &v);
    int m = *min_element(a.begin(), a.end());
    const long long INF = 1LL << 62;
    vector<long long> dist(m, INF);
    dist[0] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pending;
    pending.push({0, 0});
    while (!pending.empty())
    {
        auto current = pending.top();
        pending.pop();
        long long d = current.first;
        int r = current.second;
        if (d != dist[r])
            continue;
        for (int v : a)
        {
            int next = (r + v) % m;
            if (d + v < dist[next])
            {
                dist[next] = d + v;
                pending.push({d + v, next});
            }
        }
    }
    for (int i = 0; i < q; ++i)
    {
        long long x;
        scanf("%lld", &x);
        puts(dist[x % m] <= x ? "YES" : "NO");
    }
}
