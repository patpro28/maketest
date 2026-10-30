#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll NEG = -4000000000000000000LL;
int dim;
struct Matrix {
    ll a[6][6];
    explicit Matrix(bool identity = false) {
        for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j)
            a[i][j] = identity && i == j ? 0 : NEG;
    }
};
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < dim; ++i) for (int k = i; k < dim; ++k) if (a.a[i][k] != NEG)
        for (int j = k; j < dim; ++j) if (b.a[k][j] != NEG)
            c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
    return c;
}
Matrix power(Matrix a, ll k) {
    Matrix result(true);
    while (k) {
        if (k & 1) result = multiply(result, a);
        k >>= 1;
        if (k) a = multiply(a, a);
    }
    return result;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, c; cin >> n >> c; dim = c + 1;
    vector<Matrix> seq(n + 1);
    for (int i = 1; i <= n; ++i) {
        int type; cin >> type;
        if (type == 1) {
            int x; cin >> x; seq[i] = Matrix(true);
            for (int last = 0; last <= x; ++last) seq[i].a[last][x] = 1;
        } else if (type == 2) {
            int u, v; cin >> u >> v; seq[i] = multiply(seq[u], seq[v]);
        } else {
            int u; ll k; cin >> u >> k; seq[i] = power(seq[u], k);
        }
        ll answer = 0;
        for (int j = 0; j < dim; ++j) answer = max(answer, seq[i].a[0][j]);
        cout << answer << '\n';
    }
}
