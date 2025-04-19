#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int inv = (MOD + 1) >> 1;
const int MAX = 1e6;
int fact[MAX + 5], ifact[MAX + 5];
long long N, K;

int pow_mod(long long A, long long k) {
    long long res = 1;
    while (k) {
        if (k & 1) res = res * A % MOD;
        A = A * A % MOD;
        k >>= 1;
    }
    return res;
}

void add(int &x, const int &y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

struct Complex {
    int re, im;

    Complex(int a = 0, int b = 0) {
        re = a;
        im = b;
    }

    bool operator==(const Complex &o) { return re == o.re && im == o.im; }

    Complex operator+(const Complex &o) {
        Complex res = *this;
        add(res.re, o.re);
        add(res.im, o.im);
        return res;
    }

    Complex operator-(const Complex &o) {
        Complex res = *this;
        add(res.re, MOD - o.re);
        add(res.im, MOD - o.im);
        return res;
    }

    Complex operator*(const Complex &o) {
        Complex res;
        res.re = (1LL * re * o.re + 5LL * im * o.im) % MOD;
        res.im = (1LL * re * o.im + 1LL * im * o.re) % MOD;
        return res;
    }

    Complex operator*(int k) {
        return Complex(1LL * re * k % MOD, 1LL * im * k % MOD);
    }

    Complex pow(long long k) {
        if (k < 0) return this->pow(-k).inv();
        Complex res = Complex(1, 0), A = *this;
        while (k) {
            if (k & 1) res = res * A;
            A = A * A;
            k >>= 1;
        }
        return res;
    }

    Complex inv() {
        return Complex(re, MOD - im) *
               pow_mod((1LL * re * re + 5LL * (MOD - im) * im) % MOD, MOD - 2);
    }

    Complex operator-() { return Complex(MOD - re, MOD - im); }
};
const Complex unit = Complex(1, 0);

void factorial() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; ++i) fact[i] = 1LL * fact[i - 1] * i % MOD;
    ifact[MAX] = pow_mod(fact[MAX], MOD - 2);
    for (int i = MAX; i >= 1; --i) ifact[i - 1] = 1LL * ifact[i] * i % MOD;
}

int C(int n, int k, int p) {
    return (1LL * fact[n] * ifact[k] % p) * ifact[n - k] % p;
}

int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    factorial();
    cin >> N >> K;
    Complex res;
    for (int i = 0; i <= K; ++i) {
        Complex V1 = Complex(inv, inv).pow(2 * i - K);
        if ((K - i) & 1) V1 = -V1;

        Complex V2;

        if (V1 == unit)
            V2 = Complex((N + 1) % MOD, 0);
        else {
            V2 = V1.pow(N + 1);
            V2 = (V2 - unit) * (V1 - unit).inv();
        }

        V2 = V2 * C(K, i, MOD);

        if ((K - i) & 1)
            res = res - V2;
        else
            res = res + V2;
    }
    if (K & 1)
        cout << 1LL * res.im * pow_mod(5, MOD - 1 - K / 2) % MOD;
    else
        cout << 1LL * res.re * pow_mod(5, MOD - 1 - K / 2) % MOD;
}