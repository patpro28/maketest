/*
 * Solution:
 * Rather than going from node out, go leafs in towards root.
 * Binary lift on distances from each node towards root, then for each node nd, find furthest node
 *     towards root which is within L (call this a range)
 * Keep a counter at each node. Each counter is initially 1, and subtract 1 from every node which
 *     is the first node beyond a range
 * Simple dfs where we add counters of children to node gives the answer.
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 2e5 + 1;

int n, l;
vector<int> adj[maxn];

int bl[maxn][20];
int bll[maxn][20];
int dpth[maxn];

int cnt[maxn];

void dfs(int nd) {
    // dfs for binary lifting
    for (int i = 1; i < 20; i++) bl[nd][i] = bl[bl[nd][i - 1]][i - 1], bll[nd][i] = bll[nd][i - 1] + bll[bl[nd][i - 1]][i - 1];
    for (auto i : adj[nd]) {
        dpth[i] = dpth[bl[i][0] = nd] + 1;
        dfs(i);
    }
}

void dfs2(int nd) {
    // dfs for answer
    for (auto i : adj[nd]) {
        dfs2(i);
        cnt[nd] += cnt[i];
    }
}

signed main() {
    //freopen("main.in", "r", stdin);
    // freopen("runaway.in", "r", stdin);
    // freopen("runaway.out", "w", stdout);

    for (auto& i : cnt) i = 1;

    cin >> n >> l;

    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b; a--;
        adj[a].push_back(i);
        bll[i][0] = b;
    }

    bl[0][0] = 0, dpth[0] = 0, bll[0][0] = 0;
    dfs(0);

    // find node which is beyond distance l from node.
    for (int i = 0; i < n; i++) {
        int dst_traveled = 0, nd = i;
        for (int j = 19; j >= 0; j--) {
            if (dst_traveled + bll[nd][j] <= l) {
                dst_traveled += bll[nd][j];
                nd = bl[nd][j];
            }
        }
        if (nd != 0) cnt[bl[nd][0]]--;
    }

    dfs2(0);

    for (int i = 0; i < n; i++) cout << cnt[i] << '\n';

    return 0;
}