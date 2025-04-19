// #include <bits/allocator.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
using namespace std;
using ll = long long int;

struct FT {
	vector<ll> s;
	FT(int n = 1) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < (int) size(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	ll query(int L, int R) { // [L, R)
		return query(R) - query(L);
	}
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        vector adj(2*n, vector<int>());
        for (int i = 0; i < 2*n-1; ++i) {
            int u, v; cin >> u >> v;
            --u, --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> a(2*n);
        vector<set<int>> who(n+1);
        for (int i = 0; i < 2*n; ++i) {
            cin >> a[i];
            who[a[i]].insert(i);
        }

        const int LG = 20;
        vector<array<int, LG>> anc(2*n);
        FT through(2*n), lca_ct(2*n);
        vector<int> in(2*n), out(2*n);
        int timer = 0;
        
        auto dfs = [&] (const auto &self, int u, int p) -> void {
            anc[u][0] = p;
            in[u] = timer++;
            for (int i = 1; i < LG; ++i) anc[u][i] = anc[anc[u][i-1]][i-1];

            for (int v : adj[u]) {
                if (v != p) self(self, v, u);
            }
            out[u] = timer;
        };
        auto is_anc = [&] (int u, int v) {
            return in[u] <= in[v] and out[u] >= out[v];
        };
        auto lca = [&] (int u, int v) {
            if (is_anc(u, v)) return u;
            if (is_anc(v, u)) return v;
            for (int i = LG-1; i >= 0; --i) {
                if (!is_anc(anc[u][i], v)) u = anc[u][i];
            }
            return anc[u][0];
        };
        dfs(dfs, 0, 0);

        auto update = [&] (int col, int mul) {
            int u = *who[col].begin(), v = *who[col].rbegin();
            int L = lca(u, v);

            through.update(in[u], mul), through.update(in[v], mul);
            through.update(in[L], -mul);
            if (L > 0) through.update(in[anc[L][0]], -mul);

            lca_ct.update(in[L], mul), lca_ct.update(out[L], -mul);
        };
        auto query = [&] (int col) {
            int u = *who[col].begin(), v = *who[col].rbegin();
            int L = lca(u, v);

            int intersect = through.query(in[L], out[L]) + lca_ct.query(in[u]+1) + lca_ct.query(in[v]+1) - 2*lca_ct.query(in[L]+1);
            return n - intersect;
        };

        for (int i = 1; i <= n; ++i) update(i, 1);

        while (q--) {
            int type; cin >> type;
            if (type == 1) {
                int u, v; cin >> u >> v;
                --u, --v;
                if (a[u] == a[v]) continue;

                update(a[u], -1), update(a[v], -1);
                who[a[u]].erase(u), who[a[v]].erase(v);
                swap(a[u], a[v]);
                who[a[u]].insert(u), who[a[v]].insert(v);
                update(a[u], 1), update(a[v], 1);
            }
            else {
                int k; cin >> k;
                cout << query(k) << '\n';
            }
        }
    }
}