#include <bits/stdc++.h>
using namespace std;

#define M 1000000007

vector<vector<long long int>> dp(100005, vector<long long int>(4, 1));
vector<int> adj[100005], already(100005, 0);

void dfs(int cur, int par)
{

    for (auto next : adj[cur])
        if (next != par)
            dfs(next, cur);

    for (auto next : adj[cur])
        if (next != par)
            for (int i = 1; i <= 3; i++)
            {
                long long t = 0;
                for (int j = 1; j <= 3; j++)
                    if (i != j && dp[next][j])
                        t += (dp[next][j]);
                (dp[cur][i] *= t) %= M;
            }

    if (already[cur])
        for (int i = 1; i <= 3; i++)
            if (already[cur] != i)
                dp[cur][i] = 0;
}

int main()
{

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= k; i++)
    {
        int b, c;
        cin >> b >> c;
        already[b] = c;
    }

    dfs(1, -1);

    cout << (dp[1][1] + dp[1][2] + dp[1][3]) % M << endl;

    return 0;
}