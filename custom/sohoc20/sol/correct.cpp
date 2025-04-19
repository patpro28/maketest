/*
Author: Tu Pham Anh
Date: 2025/01/10 - 14:18
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const long long mod = 998244353;
const int inv2 = (mod + 1) >> 1;
const int N = 1e6 + 5;

int binpow(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = 1LL * res * a % mod;
        }
        a = 1LL * a * a % mod;
    }
    return res;
}

template <int base>
struct ComplexSqrt {
    long long re, im;
    
    ComplexSqrt(long long _re = 0, long long _im = 0) {
        re = _re % mod;
        im = _im % mod;
        if (re < 0)
            re += mod;
        if (im < 0)
            im += mod;
    }

    ComplexSqrt operator * (const ComplexSqrt &oth) const {
        return ComplexSqrt(
            (1LL * re * oth.re + 1LL * im * oth.im % mod * base) % mod, 
            (1LL * re * oth.im + 1LL * im * oth.re) % mod);
    }

    ComplexSqrt operator + (const ComplexSqrt &oth) const {
        return ComplexSqrt((re + oth.re) % mod, (im + oth.im) % mod);
    }

    ComplexSqrt operator - (const ComplexSqrt &oth) const {
        return ComplexSqrt((re - oth.re + mod) % mod, (im - oth.im + mod) % mod);
    }

    ComplexSqrt pow(long long b) const {
        ComplexSqrt res(1, 0), a = *this;
        for (; b; b >>= 1) {
            if (b & 1) {
                res = res * a;
            }
            a = a * a;
        }
        return res;
    }

    ComplexSqrt inv() const {
        // Nhân liên hợp
        // 1/(re, im) = (re, -im)/(re^2 - im^2 * base)
        return ComplexSqrt(re, mod - im) * binpow((1LL * re * re + 1LL * (mod - im) * im % mod * base) % mod, mod - 2);
    }

    ComplexSqrt operator / (const ComplexSqrt &oth) const {
        return *this * oth.inv();
    }

    ComplexSqrt operator * (long long x) const {
        return *this * ComplexSqrt(x, 0);
    }

    ComplexSqrt operator / (long long x) const {
        return *this / ComplexSqrt(x, 0);
    }

    bool operator == (const ComplexSqrt &oth) const {
        return re == oth.re && im == oth.im;
    }
};

ComplexSqrt<2> unit(1, 0);

int fact[N], invfact[N];

void initCombinatorial() {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) {
        fact[i] = 1LL * fact[i - 1] * i % mod;
    }
    invfact[N - 1] = binpow(fact[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; --i) {
        invfact[i] = 1LL * invfact[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return 1LL * fact[n] * invfact[k] % mod * invfact[n - k] % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    initCombinatorial();
    long long n, k;
    cin >> n >> k;
    ComplexSqrt<2> u(1, 1), v(1, -1), ans(0, 0);
    for (int i = 0, sign = 1; i <= k; ++i, sign *= -1) {
        auto cur = (u.pow(k - i)) * (v.pow(i));
        if (cur == unit)
            ans = ans + ComplexSqrt<2>(n + 1, 0) * sign * C(k, i);
        else
            ans = ans + ((cur.pow(n + 1)) - unit) / (cur - unit) * sign * C(k, i);
    }
    ans = ans / ComplexSqrt<2>(0, 2).pow(k);
    cout << ans.re << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}