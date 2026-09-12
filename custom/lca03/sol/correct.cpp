#include <bits/stdc++.h>
#define long long long

using namespace std;

const int N = (int) 3E5, K = 19;

int n;
int p[K][N], d[N];
vector<int> e[N];
vector<bool> visited(N, false);

bool DFS(int u) {
    visited[u] = true;
	for (auto v : e[u]) {
		if (v != p[0][u]) {
            if (visited[v]) return false;
			p[0][v] = u;
			d[v] = d[u] + 1;
			if (!DFS(v)) return false;
		}
	}
    return true;
}

int lift(int u, int k) {
	for (int i = K - 1; i >= 0; i--) {
		if (k >> i & 1) {
			u = p[i][u];
		}
	}
	return u;
}

int LCA(int u, int v) {
	if (d[u] > d[v]) {
		swap(u, v);
	}
	v = lift(v, d[v] - d[u]);
	if (u == v) {
		return u;
	}
	for (int i = K - 1; i >= 0; i--) {
		if (p[i][u] != p[i][v]) {
			u = p[i][u], v = p[i][v];
		}
	}
	return p[0][u];
} 

int q;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u = u - 1, v = v - 1;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	p[0][0] = -1;
	if (!DFS(0)) {
        assert(false);
    }
	for (int i = 0; i < K - 1; i++) {
		for (int u = 0; u < n; u++) {
			if (p[i][u] < 0) {
				p[i + 1][u] = -1;
			} else {
				p[i + 1][u] = p[i][p[i][u]];
			}
		}
	}
	
	cin >> q;
	for (int i = 0; i < q; i++) {
		int u, v, a;
		cin >> u >> v >> a;
		u = u - 1, v = v - 1;
		
		int x = LCA(u, v);
		if (d[u] + d[v] - d[x] * 2 <= a) {
			cout << v + 1 << "\n";
		} else {
			int b1 = d[u] - d[x];
			int b2 = d[v] - d[x];
			if (a <= b1) {
				cout << lift(u, a) + 1 << "\n";
			} else {
				cout << lift(v, b1 + b2 - a) + 1 << "\n";
			}
		}
	}
	
	return 0;
} 