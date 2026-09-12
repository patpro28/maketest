#include <bits/stdc++.h>
using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define FORall(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define sz(a) int((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
const int MOD = (int) 1e9 + 7;
const int MOD2 = 1007681537;
const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;
const ld PI = acos((ld) -1);
const ld EPS = 1e-9;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return val < a ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
inline int sign(ld x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(ld x, ld y) {return sign(x - y);}
#define db(x) cerr << #x << " = " << (x) << " ";
#define endln cerr << "\n";

const int maxn = 1e5 + 5;
const int magic = 200;
int n, q;
long long val[maxn];
int a[maxn];
int f[maxn / magic + 5][maxn];
long long g[maxn / magic + 5][maxn / magic + 5];
int cnt[maxn];

int query(int l, int r, int x) {
    return f[r][x] - f[l][x];
}

long long calchs(int l, int r) {
    long long res = 0;
    static int rem[maxn];
    int nrem = 0;
    if (r - l + 1 <= magic) {
        FOR(i, l, r + 1) {
            int x = a[i];
            if (!cnt[x]) {
                rem[nrem++] = x;
            }
            res -= val[cnt[x]];
            cnt[x]++;
            res += val[cnt[x]];
        }
        FOR(i, 0, nrem) cnt[rem[i]] = 0;
        return res;
    }
    int il = (l + magic - 1) / magic;
    int ir = r / magic;
    res = g[il][ir];
    FOR(i, l, il * magic) {
        int x = a[i];
        if (!cnt[x]) {
            cnt[x] = query(il, ir, x);
            rem[nrem++] = x;
        }
        res -= val[cnt[x]];
        cnt[x]++;
        res += val[cnt[x]];
    }
    FOR(i, ir * magic, r + 1) {
        int x = a[i];
        if (!cnt[x]) {
            cnt[x] = query(il, ir, x);
            rem[nrem++] = x;
        }
        res -= val[cnt[x]];
        cnt[x]++;
        res += val[cnt[x]];
    }
    FOR(i, 0, nrem) cnt[rem[i]] = 0;
    return res;
}

int myrand() {
    return abs(rand() * rand() + 2311 * rand() + 1992);
}

void gen() {
    srand(time(NULL));
    FOR(i, 0, maxn) val[i] = (long long) myrand() * myrand();
}

void solve() {
    gen();
    int test; scanf("%d", &test);
    assert(test >= 1 && test <= 10);
    int sumn = 0, sumq = 0;
    while (test--) {
        scanf("%d", &n);
        sumn += n;
        assert(1 <= n && n <= 7.5e4);
        FOR(i, 0, n) {
            scanf("%d", a + i), a[i]--;
            assert(0 <= a[i] && a[i] < n);
        }
        fill_n(cnt, n, 0);
        FOR(i, 0, n) {
            cnt[a[i]]++;
            if (i % magic == magic - 1) {
                int ix = i / magic + 1;
                FOR(j, 0, n) f[ix][j] = cnt[j];
            }
        }
        fill_n(cnt, n, 0);
        FOR(i, 0, maxn / magic + 5) FOR(j, 0, maxn / magic + 5) g[i][j] = 0;
        FOR(i, 0, n / magic + 5) if (i * magic < n) {
            fill_n(cnt, n, 0);
            long long f = 0;
            FOR(j, i * magic, n) {
                int x = a[j];
                f -= val[cnt[x]];
                cnt[x]++;
                f += val[cnt[x]];
                if (j % magic == magic - 1) {
                    int ix = j / magic + 1;
                    g[i][ix] = f;
                }
            }
        }
        fill_n(cnt, n, 0);
        scanf("%d", &q);
        sumq += q;
        assert(1 <= q && q <= 2e5);
        int last = 0;
        FOR(it, 0, q) {
            int x, z, c, d; scanf("%d%d%d%d", &x, &z, &c, &d); x--, z--;
            assert(0 <= x && x < n && 0 <= z && z < n);
            assert(0 <= c && c <= 1e9 && 0 <= d && d <= 1e9);
            int k = min(n - x, n - z);
            int y = x + (c + (long long) d * last) % k;
            int t = z + (c + (long long) d * last) % k;
            if (calchs(x, y) == calchs(z, t)) {
                last = it + 1;
                puts("YES");
            }
            else {
                puts("NO");
            }
        }
    }
    assert(sumn <= 1.5e5 && sumq <= 4e5);
}

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        freopen(argv[1], "r", stdin);
    }
    if (argc >= 3) {
        freopen(argv[2], "wb", stdout);
    }
    solve();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}