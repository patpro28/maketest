#include <algorithm>
#include <array>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;
using Key = uint64_t;
const int M1 = 1000000007, M2 = 1000000009, BASE = 911382323;
struct Hash
{
    vector<int> a, b, p, q;
    explicit Hash(const vector<ll> &s) : a(s.size() + 1), b(s.size() + 1), p(s.size() + 1, 1), q(s.size() + 1, 1)
    {
        for (int i = 0; i < (int)s.size(); ++i)
        {
            ll x = (s[i] % M1 + M1) % M1, y = (s[i] % M2 + M2) % M2;
            a[i + 1] = (a[i] * (ll)BASE + x) % M1;
            b[i + 1] = (b[i] * (ll)BASE + y) % M2;
            p[i + 1] = p[i] * (ll)BASE % M1;
            q[i + 1] = q[i] * (ll)BASE % M2;
        }
    }
    explicit Hash(const string &s) : Hash(vector<ll>(s.begin(), s.end())) {}
    Key get(int l, int r) const
    { // Half-open interval [l,r).
        ll x = (a[r] - a[l] * (ll)p[r - l] % M1 + M1) % M1;
        ll y = (b[r] - b[l] * (ll)q[r - l] % M2 + M2) % M2;
        return (Key(x) << 32) | Key(y);
    }
};
struct KeyHash
{
    size_t operator()(Key x) const
    { // Deterministic mixing; generation remains reproducible.
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
};
struct GridHash
{
    int r, c;
    vector<int> a, b, pr, pc, qr, qc;
    explicit GridHash(const vector<string> &s) : r(s.size()), c(s[0].size()), a((r + 1) * (c + 1)), b(a.size()), pr(r + 1, 1), pc(c + 1, 1), qr(r + 1, 1), qc(c + 1, 1)
    {
        const int X = 911382323, Y = 972663749;
        for (int i = 1; i <= r; ++i)
        {
            pr[i] = pr[i - 1] * (ll)X % M1;
            qr[i] = qr[i - 1] * (ll)X % M2;
        }
        for (int j = 1; j <= c; ++j)
        {
            pc[j] = pc[j - 1] * (ll)Y % M1;
            qc[j] = qc[j - 1] * (ll)Y % M2;
        }
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
            {
                int t = i * (c + 1) + j;
                ll x = (a[t - c - 1] * (ll)X + a[t - 1] * (ll)Y - a[t - c - 2] * (ll)X % M1 * Y + s[i - 1][j - 1]) % M1;
                ll y = (b[t - c - 1] * (ll)X + b[t - 1] * (ll)Y - b[t - c - 2] * (ll)X % M2 * Y + s[i - 1][j - 1]) % M2;
                a[t] = (x + M1) % M1;
                b[t] = (y + M2) % M2;
            }
    }
    Key get(int x, int y, int d) const
    {
        int t = (x + d) * (c + 1) + y + d, u = x * (c + 1) + y + d, v = (x + d) * (c + 1) + y, w = x * (c + 1) + y;
        ll h = (a[t] - a[u] * (ll)pr[d] - a[v] * (ll)pc[d] + a[w] * (ll)pr[d] % M1 * pc[d]) % M1;
        ll g = (b[t] - b[u] * (ll)qr[d] - b[v] * (ll)qc[d] + b[w] * (ll)qr[d] % M2 * qc[d]) % M2;
        return (Key((h + M1) % M1) << 32) | Key((g + M2) % M2);
    }
};
vector<string> rotate_grid(const vector<string> &s)
{
    int r = s.size(), c = s[0].size();
    vector<string> t(c, string(r, ' '));
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            t[j][r - 1 - i] = s[i][j];
    return t;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, q;
    cin >> r >> c >> q;
    vector<string> s(r);
    for (auto &x : s)
        cin >> x;
    vector<GridHash> h;
    for (int t = 0; t < 4; ++t)
    {
        h.emplace_back(s);
        s = rotate_grid(s);
    }
    while (q--)
    {
        int x, y, u, v, d;
        cin >> x >> y >> u >> v >> d;
        --x;
        --y;
        --u;
        --v;
        Key target = h[0].get(x, y, d);
        bool ok = false;
        int height = r, width = c;
        for (int t = 0; t < 4; ++t)
        {
            ok |= h[t].get(u, v, d) == target;
            int a = v, b = height - u - d;
            u = a;
            v = b;
            swap(height, width);
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
