/**
 *    author:  longvu
 *    created: 11/02/24 21:10:19
**/
#include<bits/stdc++.h>

using namespace std;

#define sz(x) ((int)x.size())
#define all(x) (x).begin(), (x).end()
const int INF = numeric_limits<int>::max();
const int nax = (int)(101001);
const int mod = 998244353;

template<class X, class Y>
bool maximize(X& x, const Y y) {
    if (y > x) {x = y; return true;}
    return false;
}
template<class X, class Y>
bool minimize(X& x, const Y y) {
    if (y < x) {x = y; return true;}
    return false;
}

template<int MOD>
struct ModInt {
    unsigned x;
    ModInt() : x(0) { }
    ModInt(signed long long sig) : x(sig % MOD + (sig < 0 ? MOD : 0)) { }
    int get() const { return (int)x; }

    ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
    ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
    ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }

    ModInt expo(ModInt a, int b) {
        if (!b) {
            return 1;
        }
        ModInt tmp = expo(a, b >> 1);
        if (b & 1) {
            return tmp * tmp * a;
        }
        return tmp * tmp;
    }
    ModInt &operator/=(ModInt that) { return (*this) *= expo(that, MOD - 2); }

    ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
    ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
    ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
    ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
    ModInt operator^(int that) { return expo(ModInt(*this), that); } // BE CAREFUL
    bool operator<(ModInt that) const { return x < that.x; }
    friend ostream& operator<<(ostream &os, ModInt a) { os << a.x; return os; }
};
typedef ModInt<mod> mint;

int gcd(int a, int b) {
    return (!b ? a : gcd(b, a % b));
}

mint sum[nax], mobius[nax], pre[nax], pw2[6 * nax];
vector<int> divisor[nax];
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    pw2[0] = 1;
    for (int i = 1; i < 6 * nax; ++i) {
        pw2[i] = mint(2) * pw2[i - 1];
    }
    mobius[1] = 1;
    int mx = 0;
    for (int i = 1; i < nax; ++i) {
        divisor[i].push_back(i);
        for (int j = 2 * i; j < nax; j += i) {
            divisor[j].push_back(i);
            mobius[j] -= mobius[i];
        }
        maximize(mx, sz(divisor[i]));
    }
    // cout << mx << '\n';
    for (int i = 1; i < nax; ++i) {
        for (auto v : divisor[i]) {
            pre[i] += mobius[i / v] * v;
        }
    }
    int n;
    cin >> n;
    mint ans = 0;
    for (int t = 1; t <= n; ++t) {
        int x;
        cin >> x;
        ans *= 2;
        for (auto &u : divisor[x]) {
            ans += pre[u] * sum[u];
        }
        for (auto &u : divisor[x]) {
            sum[u] += pw2[t - 1];
        }
        cout << ans << '\n';
    }
    return 0;
}