#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll NEG = -4000000000000000000LL;
struct Matrix {
    ll a[7][7];
    explicit Matrix(bool identity = false) {
        for (int i = 0; i < 7; ++i) for (int j = 0; j < 7; ++j)
            a[i][j] = identity && i == j ? 0 : NEG;
    }
};
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < 7; ++i) for (int k = 0; k < 7; ++k) if (a.a[i][k] != NEG)
        for (int j = 0; j < 7; ++j) if (b.a[k][j] != NEG)
            c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
    return c;
}
Matrix day(const array<ll, 3>& score) {
    Matrix a;
    for (int i = 0; i < 7; ++i) a.a[i][0] = 0;
    for (int j = 0; j < 3; ++j) {
        a.a[0][j + 1] = score[j];
        for (int last = 0; last < 3; ++last) if (last != j)
            a.a[last + 1][j + 4] = score[j];
    }
    return a;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int p; ll days; cin >> p >> days;
    Matrix cycle(true), prefix(true);
    const int rem = int(days % p);
    for (int i = 0; i < p; ++i) {
        array<ll, 3> a; for (auto& x : a) cin >> x;
        Matrix m = day(a); cycle = multiply(cycle, m);
        if (i < rem) prefix = multiply(prefix, m);
    }
    ll times = days / p; Matrix result(true);
    while (times) {
        if (times & 1) result = multiply(result, cycle);
        times >>= 1;
        if (times) cycle = multiply(cycle, cycle);
    }
    result = multiply(result, prefix);
    cout << *max_element(result.a[0], result.a[0] + 7) << '\n';
}
