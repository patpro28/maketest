#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

const int N = 1e6 + 7;
const int P = 40;

int n, q;
uint w[N];
vector <int> G[N];

int id[N];
int off[N];
int to_add[N];

bool mem[10 * N];
uint ans[10 * N];

uint dot[N];
int lvl[N], par[N];
vector <int> ver_list[N];

void dfs(int u, int p){
	par[u] = p;
	ver_list[lvl[u]].push_back(u);

	dot[u] += w[u] * w[u];
	for(auto v: G[u])
		if(v != p){
			dot[v] = dot[u];
			lvl[v] = lvl[u] + 1;
			dfs(v, u);
		}
}

void read(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%u", &w[i]);

	for(int i = 1; i < n; ++i){
		int u, v;
		scanf("%d %d", &u, &v);

		G[u].push_back(v);
		G[v].push_back(u);
	}
}

void init(){
	read();
	dfs(1, 0);

	int off_count = 0;
	for(int i = 0; i < n; i += P){
		int best = i;
		for(int j = 0; j < P; ++j)
			if(ver_list[i + j].size() < ver_list[best].size())
				best = i + j;

		int t = 0;
		for(auto &v: ver_list[best])
			id[v] = t++;

		off[best] = off_count;
		off_count += t * (t - 1) / 2;
	}
}

uint answer(int u, int v){
	uint ret = 0;
	int it = 0;

	while(u != v){
		int cur_lvl = lvl[u];
		if(off[cur_lvl] > 0){
			int pu = id[u], pv = id[v];
			if(pu < pv)
				swap(pu, pv);

			int place = off[cur_lvl] + pu * (pu - 1) / 2 + pv;

			if(mem[place]){
				ret += ans[place];
				for(int i = 0; i < it; ++i)
					ans[to_add[i]] += ret;
				return ret;
			}

			mem[place] = true;
			ans[place] = -ret;

			to_add[it++] = place;
			ret += w[u] * w[v];
		}
		else
			ret += w[u] * w[v];

		u = par[u], v = par[v];
	}

	ret += dot[u];
	for(int i = 0; i < it; ++i)
		ans[to_add[i]] += ret;
	return ret;
}

void solve(){
	while(q--){
		int u, v;
		scanf("%d %d", &u, &v);
		printf("%u\n", answer(u, v));
	}
}

int main(){
	init();
	solve();
	return 0;
}