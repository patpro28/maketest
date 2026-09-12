#include <iostream>
#include <functional>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int find_diameter(vector<pair<int, int>> &edges, int n) {
    vector<vector<int>> adj(n + 1);
    for (auto e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    vector<int> dist(n + 1, -1);
    int diameter = 0;
    function<void(int, int)> dfs = [&](int at, int parent) {
        dist[at] = 1;
        for (auto to : adj[at]) {
            if (to == parent) continue;
            dfs(to, at);
            diameter = max(diameter, dist[at] + dist[to]);
            dist[at] = max(dist[at], dist[to] + 1);
        }
    };
    dfs(1, -1);
    return diameter;
} 

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 20);
    int q = gen.uniform(1, 100);
    cout << n << '\n';
    auto edges = gen.tree<int>(n, true);
    for (auto e : edges) {
        cout << e.first << ' ' << e.second << '\n';
    }
    int diameter = find_diameter(edges, n);
    cout << q << '\n';
    for (int i = 0; i < q; i++) {
        int a = gen.uniform(1, n);
        int b = gen.uniform(1, n);
        int c = gen.uniform(0, diameter);
        cout << a << ' ' << b << ' ' << c << '\n';
    }
    return 0;
}
