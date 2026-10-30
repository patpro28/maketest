#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll NEG = -4000000000000000000LL;
struct Matrix {
    ll a[3][3];
    explicit Matrix(bool identity = false) {
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j)
            a[i][j] = identity && i == j ? 0 : NEG;
    }
};
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < 3; ++i) for (int k = 0; k < 3; ++k) if (a.a[i][k] != NEG)
        for (int j = 0; j < 3; ++j) if (b.a[k][j] != NEG)
            c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
    return c;
}
Matrix leaf(ll w) {
    Matrix m; m.a[0][0] = m.a[1][0] = m.a[2][1] = 0; m.a[0][2] = w;
    return m;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    int size = 1; while (size < n) size *= 2;
    vector<Matrix> tree(2 * size, Matrix(true));
    for (int i = 0; i < n; ++i) { ll x; cin >> x; tree[size + i] = leaf(x); }
    for (int i = size - 1; i; --i) tree[i] = multiply(tree[2*i], tree[2*i+1]);
    while (q--) {
        int type, x; ll y; cin >> type >> x >> y;
        if (type == 1) {
            int p = size + x - 1; tree[p] = leaf(y);
            while (p >>= 1) tree[p] = multiply(tree[2*p], tree[2*p+1]);
        } else {
            int l = size + x - 1, r = size + int(y);
            Matrix left(true), right(true);
            while (l < r) {
                if (l & 1) left = multiply(left, tree[l++]);
                if (r & 1) right = multiply(tree[--r], right);
                l >>= 1; r >>= 1;
            }
            Matrix result = multiply(left, right);
            cout << *max_element(result.a[0], result.a[0]+3) << '\n';
        }
    }
}
