/*Code by TMQ*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define ii pair<ll, ll>
#define fi first
#define se second
#define pb push_back
#define em emplace
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)
#define FIV(i, a, b) for (int i = (a), _b = (b); i >= _b; i--)
#define all(x) (x).begin(), (x).end()
#define reset(a, x) (memset(a, x, sizeof(a)));
#define Unique(v) v.erase(unique(all(v)), v.end());
#define testcase \
    int tc;      \
    cin >> tc;   \
    while (tc--) \
        solve();
#define howlong cerr << "Time elapsed: " << fixed << setprecision(9) << (double)clock() / CLOCKS_PER_SEC << "s";
#define what_is(x) cerr << #x << " is " << x << '\n';
ll inline GCD(ll a, ll b) { return !b ? abs(a) : GCD(b, a % b); }
ll inline LCM(ll a, ll b) { return (a / GCD(a, b) * b); }
template <class X, class Y>
bool maximize(X &x, Y y)
{
    if (x < y)
    {
        x = y;
        return true;
    }
    return false;
};
template <class X, class Y>
bool minimize(X &x, Y y)
{
    if (x > y)
    {
        x = y;
        return true;
    }
    return false;
};
///=====================================s========================================
#define BIT(i, mask) ((mask >> (i)) & 1)
#define DAOBIT(i, mask) ((mask ^ (1 << i)))
#define OFFBIT(i, mask) ((mask & ~(1 << (i))))
#define ONBIT(i, mask) ((mask | (1 << (i))))
///============================================================================
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)                   \
    {                                 \
        cerr << "[" << #x << "] = ["; \
        _print(x);                    \
    }
#else
#define debug(x...)
#endif
///============================================================================
void TASK(string task)
{
    if (fopen((task + ".inp").c_str(), "r"))
    {
        freopen((task + ".inp").c_str(), "r", stdin);
        freopen((task + ".out").c_str(), "w", stdout);
    }
}
///============================================================================
const ll mod = 1e9 + 7;
const ll inf = (ll)1e18 + 10;
const ll nmax = 2e5 + 5;
///============================================================================
string s;
int cnt[nmax], n;
int cal0(int l, int r)
{
    if (l > r)
        return 0;
    return cnt[r] - cnt[l - 1];
}
int cal1(int l, int r)
{
    if (l > r)
        return 0;
    return r - l + 1 - cnt[r] + cnt[l - 1];
}
void solve()
{
    cin >> s;
    /// debug(s);
    n = s.size();
    s = ' ' + s;
    for (int i = 1; i <= n; i++)
        cnt[i] = cnt[i - 1] + (s[i] == '0');
    int res = n - cnt[n];
    for (int i = 1; i <= n; i++)
    {
        int l = i, r = n, mid;
        while (l < r)
        {
            mid = (l + r) >> 1;
            /// debug(l, r, mid);
            if (cal0(i, mid) < cal1(1, i - 1) + cal1(mid + 1, n))
                l = mid + 1;
            else
                r = mid;
        }
        /// debug(i, l, r);
        res = min(res, max(cal0(i, r), cal1(1, i - 1) + cal1(r + 1, n)));
    }
    cout << res << '\n';
}
///============================================================================
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    TASK("name");
    testcase;
}