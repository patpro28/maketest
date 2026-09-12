#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int N = 3e5 + 7;

vector <int> ver_list[N], G[N];
int lvl[N], max_lvl = 0;

void dfs(int u, int p){
	ver_list[lvl[u]].push_back(u);
    max_lvl = max(max_lvl, lvl[u]);
	for(auto v: G[u])
		if(v != p){
			lvl[v] = lvl[u] + 1;
			dfs(v, u);
		}
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(10, 3e5);
    int q = gen.uniform<int>(10, 3e5);
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform<int>(1, 1e9) << (i == n - 1 ? "\n" : " ");
    }
    auto tree = gen.tree_depth<int>(n, true, 3);
    for (int i = 0; i < n - 1; ++i) {
        cout << tree[i].first << " " << tree[i].second << "\n";
        G[tree[i].first].push_back(tree[i].second);
        G[tree[i].second].push_back(tree[i].first);
    }
    dfs(1, 0);
    for (int i = 0; i < q; ++i) {
        int k = gen.uniform<int>(1, max_lvl);
        int m = (int) ver_list[k].size();
        int u = ver_list[k][gen.uniform<int>(0, m - 1)];
        int v = ver_list[k][gen.uniform<int>(0, m - 1)];
        cout << u << " " << v << "\n";
    }
}
