/**
 *     author:  NguyenTanDat
 *     created: 20.12.2024 01:07:41
**/
#include <bits/stdc++.h>

using namespace std;

//===================================//
#define faster                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
//===================================//

#define fo(i, x, n) for (int i = x; i <= n; ++i)
#define fi(i, x, n) for (int i = x; i >= n; --i)
#define eb emplace_back
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll // uint64_t
#define ui unsigned int // uint32_t
#define DAOBIT(i, mask) ((mask ^ (1ll << i))) // 0 -> 1 and 1 -> 0
#define OFFBIT(i, mask) ((mask & ~(1ll << i)))
#define ONBIT(i, mask) ((mask | (1ll << i)))
#define BIT(i, mask) ((mask >> i) & 1)
#define SETBIT(i, mask) (mask | (1 << i)); // 0 -> 1 and 1 -> 1
// __builtin_popcountll(x) : dem so luong bit 1 trong x
// __builtin_clzll(x) : dem so luong bit 0 o dau
// __builtin__ctzll(x) : dem so luong bit 0 o cuoi
// __lq(x) + 1 : tra ve do dai bitmask 

void fre()
{
    freopen("name.inp", "r", stdin);
    freopen("name.out", "w", stdout);
}
const ll nmax = 1e5 + 5;
ll n, sum[nmax], a[nmax], q[nmax], m;
void sol()
{
    cin >> n;
    fo(i, 1, n){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    cin >> m;
    fo(i, 1, m){
        cin >> q[i];
        ll pos = lower_bound(sum + 1, sum + n + 1, q[i]) - sum;
        cout << pos << '\n';
    }
}

signed main()
{
    // fre();
    faster
    sol();
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}