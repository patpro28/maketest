#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
using ll = long long;
const ll NEG = -4000000000000000000LL;
using Matrix = vector<vector<ll>>;

struct Node {
    array<int, 3> next{{-1, -1, -1}};
    int link = 0;
    ll score = 0;
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    int n = int(a.size());
    Matrix c(n, vector<ll>(n, NEG));
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k) if (a[i][k] != NEG)
            for (int j = 0; j < n; ++j) if (b[k][j] != NEG)
                c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m; ll length;
    cin >> m >> length;
    vector<Node> ac(1);
    for (int i = 0; i < m; ++i) {
        string s; ll w; cin >> s >> w;
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (ac[u].next[c] == -1) {
                ac[u].next[c] = int(ac.size());
                ac.emplace_back();
            }
            u = ac[u].next[c];
        }
        ac[u].score += w;
    }
    queue<int> bfs;
    for (int c = 0; c < 3; ++c) {
        if (ac[0].next[c] == -1) ac[0].next[c] = 0;
        else bfs.push(ac[0].next[c]);
    }
    while (!bfs.empty()) {
        int u = bfs.front(); bfs.pop();
        ac[u].score += ac[ac[u].link].score;
        for (int c = 0; c < 3; ++c) {
            int v = ac[u].next[c];
            if (v == -1) ac[u].next[c] = ac[ac[u].link].next[c];
            else {
                ac[v].link = ac[ac[u].link].next[c];
                bfs.push(v);
            }
        }
    }
    int n = int(ac.size());
    Matrix power(n, vector<ll>(n, NEG));
    for (int u = 0; u < n; ++u) for (int c = 0; c < 3; ++c) {
        int v = ac[u].next[c];
        power[u][v] = max(power[u][v], ac[v].score);
    }
    vector<ll> best(n, NEG); best[0] = 0;
    while (length) {
        if (length & 1) {
            vector<ll> next(n, NEG);
            for (int u = 0; u < n; ++u) if (best[u] != NEG)
                for (int v = 0; v < n; ++v) if (power[u][v] != NEG)
                    next[v] = max(next[v], best[u] + power[u][v]);
            best.swap(next);
        }
        length >>= 1;
        if (length) power = multiply(power, power);
    }
    cout << *max_element(best.begin(), best.end()) << '\n';
}
