/*Code by TMQ*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define ii pair<int, int>
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
const int mod = 1e9 + 7;
const int inf = 1e9 + 10;
const int nmax = 500 + 5;
int B = 500;
///============================================================================
int n, x, y;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int du[nmax * nmax], dv[nmax * nmax];
int ans[nmax * nmax];
int dist(int x, int y, int u, int v)
{
    return abs(x - u) + abs(y - v);
}
int res;
int dp[nmax][nmax];
void case2(int st, int en)
{
    queue<ii> q;
    for(int i = st; i <= en; i++)
    {
        int u = du[i], v = dv[i];
        dp[u][v] = 0;
        q.push({u, v});
    }
    while(!q.empty())
    {
        int x = q.front().fi, y = q.front().se;
        q.pop();
        for(int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= n)
            {
                if(dp[nx][ny] > dp[x][y] + 1)
                {
                    dp[nx][ny] = dp[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
}
///============================================================================
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    TASK("test");
    cin >> n >> x >> y;
    ///B = n;
    du[0] = x, dv[0] = y;
    for(int i = 1; i <= n * n - 1; i++)
        {
            ans[i] = inf;
            cin >> du[i] >> dv[i];
        }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = inf;
    dp[x][y] = 0;
    for(int i = 1; i <= n * n - 1; i += B)
    {
        int st = i, en = min(n * n - 1, i + B - 1);
        for(int j = en; j >= st + 1; j--)
        {
            int u = du[j], v = dv[j];
            min(ans[j], dist(u, v, du[0], dv[0]));
            for(int k = j - 1; k >= st; k--)
            {
                int x = du[k], y = dv[k];
                minimize(ans[j], dist(u, v, x, y));
            }
        }
        for(int j = st; j <= en; j++)
        {
            int u = du[j], v = dv[j];
            minimize(ans[j], dist(u, v, du[0], dv[0]));
            ///debug(u, v, du[0], dv[0], dist(u, v, du[0], dv[0]));
            minimize(ans[j], dp[u][v]);
        }
        case2(st, en);
    }
    for(int i = 1; i <= n * n - 1; i++)
        cout << ans[i] << ' ';

}