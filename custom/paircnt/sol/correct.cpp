#include<bits/stdc++.h>
using namespace std;

#define N 100010
#define L 20
#define M 1000

vector<int> nei[N];
int t, n, q, k, D, x[N];

int timer, id;
int LST[N << 1][L], AST[N << 1][L];
int start_time[N], deep[N], pa[N];

void dfs(int u, int par, int lev) {
    start_time[u] = timer ++;
    deep[u] = lev;
    pa[u] = par;

    LST[id][0] = lev;
    AST[id][0] = u;
    id ++;

    for(int v : nei[u]) if(v != pa[u]) {
        dfs(v, u, lev + 1);
        LST[id][0] = lev;
        AST[id][0] = u;
        id ++;
    }
    timer ++;
}

void prepare() {
    for(int j = 1; (1 << j) <= id; j ++) {
        for(int i = 0; (i + (1 << j) - 1) < id; i ++) {
            if(LST[i][j - 1] < LST[i + (1 << (j - 1))][j - 1]) {
                LST[i][j] = LST[i][j - 1];
                AST[i][j] = AST[i][j - 1];
            }
            else {
                LST[i][j] = LST[i + (1 << (j - 1))][j - 1];
                AST[i][j] = AST[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int LCA(int u,int v) {
    int l = min(start_time[u], start_time[v]);
    int r = max(start_time[u], start_time[v]);
    int p = 31 - __builtin_clz(r - l + 1);
    if(LST[l][p] <= LST[r - (1 << p) + 1][p]) return AST[l][p];
    return AST[r - (1 << p) + 1][p];
}

int dist(int u, int v) {
    return deep[u] + deep[v] - 2 * deep[LCA(u, v)];
}

long long ans;
int tot[N];
map<int, int> cnt[N];

void merge(int u, int v) {
    if(cnt[u].size() < cnt[v].size()) swap(cnt[u], cnt[v]);
    for(auto p : cnt[v]) {
        int d = 2 * deep[u] + D - p.first;
        if(cnt[u].count(d)) ans += 1ll * cnt[u][d] * p.second;
    }
    for(auto p : cnt[v]) {
        cnt[u][p.first] += p.second;
    }
    cnt[v].clear();
}

void count_dfs(int u) {
    cnt[u].clear();
    if(tot[u]) cnt[u][deep[u]] = tot[u];
    for(int v : nei[u]) if(v != pa[u]) {
        count_dfs(v);
        merge(u, v);
    }
}

int main() {
    for(scanf("%d", &t); t --; ) {
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i ++) nei[i].clear();
        for(int i = 1, u, v; i < n; i ++) {
            scanf("%d%d", &u, &v);
            nei[u].push_back(v);
            nei[v].push_back(u);
        }
        timer = id = 0;
        dfs(1, 0, 0);
        prepare();
        while(q --) {
            scanf("%d%d", &k, &D);
            for(int i = 1; i <= k; i ++) scanf("%d", &x[i]), tot[x[i]] ++;
            ans = 0;
            if(D == 0) {
                for(int i = 1; i <= k; i ++) ans += -- tot[x[i]];
            }
            else if(k <= M) {
                for(int i = 1; i <= k; i ++) for(int j = i + 1; j <= k; j ++) ans += (dist(x[i], x[j]) == D);
            }
            else {
                count_dfs(1);
            }
            printf("%lld\n", ans);
            for(int i = 1; i <= k; i ++) tot[x[i]] = 0;
        }
    }
}
