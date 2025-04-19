#include <bits/stdc++.h>
using namespace std;

int main()
{
    // your code goes here
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<array<int, 3>> ans;
        auto dfs = [&](auto &&dfs, int node, int par) -> void
        {
            for (auto it : adj[node])
            {
                if (it != par)
                {
                    dfs(dfs, it, node);
                    ans.push_back({node, it, it});
                }
            }
        };
        dfs(dfs, 1, 0);
        if (n != 2)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << 1 << endl;
        }
        if (n >= 4 && n % 2 == 0)
        {
            ans[n - 3][2] = ans[n - 3][0];
            ans[n - 4][2] = ans[n - 4][0];
        }
        for (auto it : ans)
        {
            cout << it[0] << " " << it[1] << " " << it[2] << endl;
        }
    }
}