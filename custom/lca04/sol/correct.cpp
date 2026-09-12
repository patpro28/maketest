#include <bits/stdc++.h>
using namespace std;

const int N = 3e5;
bool connected[N + 5];
int parent[N + 5], idx[N + 5];
 
struct Link 
{
    int u, v, weight;
}; Link edges[N + 5], queries[N + 5];
 
bool cmpEdge(const Link &A, const Link &B) 
{
    return A.weight < B.weight;
}
 
bool cmpIdx(const int &A, const int &B) 
{
    return cmpEdge(queries[A], queries[B]);
}
 
int findParent(int x) 
{
    return (parent[x] == x) ? x : (parent[x] = findParent(parent[x]));
}
 
int main() 
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m;
    cin >> n;
    for(int i = 0; i < n; ++i) 
        parent[i] = i;
    --n;
    for(int i = 0; i < n; ++i) 
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        --edges[i].u;
        --edges[i].v;
    }
    sort(edges, edges + n, cmpEdge);
    cin >> m;
    for(int i = 0; i < m; ++i) 
    {
        idx[i] = i;
        cin >> queries[i].u >> queries[i].v >> queries[i].weight;
        --queries[i].u;
        --queries[i].v;
    }
    sort(idx, idx + m, cmpIdx);
    for (int i = 0, j = 0; i < m; ++i) 
    {
        for (; j < n && edges[j].weight <= queries[idx[i]].weight; ++j) 
        {
            int pu = findParent(edges[j].u), pv = findParent(edges[j].v);
            parent[pu] = pv;
        }
        connected[idx[i]] = findParent(queries[idx[i]].u) != findParent(queries[idx[i]].v);
    }
    for(int i = 0; i < m; ++i) 
        puts(connected[i] ? "YES" : "NO");
    return 0;
}