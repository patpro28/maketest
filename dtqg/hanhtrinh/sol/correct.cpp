#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll NEG = -4000000000000000000LL;
using Matrix = vector<vector<ll>>;
Matrix multiply(const Matrix& a, const Matrix& b) {
    int n = int(a.size()); Matrix c(n, vector<ll>(n, NEG));
    for (int i = 0; i < n; ++i) for (int k = 0; k < n; ++k) if (a[i][k] != NEG)
        for (int j = 0; j < n; ++j) if (b[k][j] != NEG)
            c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
    return c;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, s, t; ll steps; cin >> n >> m >> s >> t >> steps; --s; --t;
    Matrix a(n, vector<ll>(n, NEG)), result(n, vector<ll>(n, NEG));
    for (int i = 0; i < n; ++i) result[i][i] = 0;
    for (int i = 0; i < m; ++i) {
        int u, v; ll w; cin >> u >> v >> w; --u; --v;
        a[u][v] = max(a[u][v], w);
    }
    while (steps) {
        if (steps & 1) result = multiply(result, a);
        steps >>= 1;
        if (steps) a = multiply(a, a);
    }
    if (result[s][t] == NEG) cout << "IMPOSSIBLE\n";
    else cout << result[s][t] << '\n';
}
