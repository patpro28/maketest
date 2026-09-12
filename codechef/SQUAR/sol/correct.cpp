#include <bits/stdc++.h>

#define ll long long int
#define vl vector<ll>
#define vpl vector<pair<ll, ll>>
#define umpl unordered_map<ll, ll>
#define mpl map<ll, ll>
#define pl pair<ll, ll>

#define pb push_back
#define f first
#define s second

#define fr(i, start, end) for (ll i = start; i < end; i++)
#define frr(i, end, start) for (ll i = end; i > start; i--)
#define all(x) (x).begin(), (x).end()

using namespace std;
const int MOD = 1e9 + 7;

typedef vector<int, int> vi;
typedef pair<int, int> pi;
typedef unordered_map<int, int> mi;

ll fast_pow(ll b, ll e, ll width = MOD)
{
    if (e == 0)
        return 1;
    else if (e == 1)
        return b % width;
    b = b % width;
    ll ans = 1;
    while (e > 0)
    {
        if ((e & 1) == 1)
            ans = (ans * b) % width;
        e >>= 1;
        b = (b * b) % width;
    }
    return ans;
}

ll fast_mul(ll a, ll b) { return ((a % MOD) * (b % MOD)) % MOD; }

ll binpow(ll a, ll b)
{
    if (b == 0)
        return 1;
    int ans = binpow(a, b / 2);
    ans = fast_mul(ans, ans);
    if (b % 2)
    {
        return fast_mul(ans, a);
    }
    return ans;
}

ll mod_inv(ll a, ll p = MOD)
{
    return binpow(a, p - 2);
}

ll fact(ll n);

ll nCr(ll n, ll r)
{
    return fact(n) / (fact(r) * fact(n - r));
}

// Returns factorial of n
ll fact(ll n)
{
    if (n == 0)
        return 1;
    ll res = 1;
    for (ll i = 2; i <= n; i++)
        res = (res * i) % LLONG_MAX;
    return res;
}

bool isPerfectSquare(int n)
{
    // Base case: 0 and 1 are perfect squares
    if (n <= 1)
    {
        return true;
    }

    // Initialize boundaries for binary search
    ll left = 1, right = n;

    while (left <= right)
    {

        // Calculate middle value
        ll mid = left + (right - left) / 2;

        // Calculate square of the middle value
        ll square = mid * mid;

        // If the square matches n, n is a perfect square
        if (square == n)
        {
            return true;
        }

        // If the square is smaller than n, search the right
        // half
        else if (square < n)
        {

            left = mid + 1;
        }

        // If the square is larger than n, search the left
        // half
        else
        {

            right = mid - 1;
        }
    }

    // If the loop completes without finding a perfect
    // square, n is not a perfect square
    return false;
}

#define MAXN 10000001

// stores smallest prime factor for every number
int spf[MAXN];

// Calculating SPF (Smallest Prime Factor) for every
// number till MAXN.
// Time Complexity : O(nloglogn)
void sieve()
{
    spf[1] = 1;
    for (int i = 2; i < MAXN; i++)

        // marking smallest prime factor for every
        // number to be itself.
        spf[i] = i;

    // separately marking spf for every even
    // number as 2
    for (int i = 4; i < MAXN; i += 2)
        spf[i] = 2;

    for (int i = 3; i * i < MAXN; i++)
    {
        // checking if i is prime
        if (spf[i] == i)
        {
            // marking SPF for all numbers divisible by i
            for (int j = i * i; j < MAXN; j += i)

                // marking spf[j] if it is not
                // previously marked
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}

vector<int> p;
unordered_map<int, int> ps;

// A O(log n) function returning primefactorization
// by dividing by smallest prime factor at every step
void getFactorization(int i)
{
    unordered_map<int, int> m;
    int x = p[i];
    while (x != 1)
    {
        m[spf[x]]++;
        x = x / spf[x];
    }

    vector<int> ff;
    for (auto e : m)
    {
        if (e.s % 2)
            ff.pb(e.f);
    }

    if (ff.size() == 1)
        ps[ff[0]]++;
    else
    {
        int prod = 1;
        for (auto e : ff)
            prod *= e;
        ps[prod]++;
    }
}

void solve()
{
    p.clear();
    ps.clear();

    int n;
    cin >> n;

    int t;
    fr(i, 0, n)
    {
        cin >> t;
        if (isPerfectSquare(t))
            continue;

        p.pb(t);
    }

    n = p.size();

    fr(i, 0, n) getFactorization(i);

    int ans = 0;

    for (auto e : ps)
    {
        ans = max(ans, e.s);
    }

    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll T = 1;
    cin >> T;
    sieve();
    while (T--)
        solve();
    return 0;
}