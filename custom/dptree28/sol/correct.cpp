#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, target; cin >> n >> target;
    vector<int> type(n);
    vector<array<int,2>> child(n);
    vector<array<ll,3>> dp(n);
    for (int u = 0; u < n; ++u) {
        cin >> type[u];
        if (type[u] == 0) for (ll &c : dp[u]) cin >> c;
        else {
            cin >> child[u][0] >> child[u][1];
            --child[u][0]; --child[u][1];
        }
    }
    vector<int> order{0};
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (type[u]) for (int v : child[u]) order.push_back(v);
    }
    const ll INF = 1LL << 60;
    for (int i = n-1; i >= 0; --i) {
        int u = order[i];
        if (type[u] == 0) continue;
        dp[u] = {INF,INF,INF};
        int x = child[u][0], y = child[u][1];
        for (int a = 0; a < 3; ++a) for (int b = 0; b < 3; ++b) {
            int r = (type[u] == 1 ? a+b : a*b) % 3;
            dp[u][r] = min(dp[u][r], dp[x][a] + dp[y][b]);
        }
    }
    cout << dp[0][target] << '\n';
}
