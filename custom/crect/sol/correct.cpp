#include <cstdio>
#include <iostream>
#include <cstring>
#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define REP(i, a, b) for(int i = (a); i <=(b); ++i)
#define REPD(i, a, b) for(int i = (a); i >= (b); --i)
#define RESET(a, v) memset(a, (v), sizeof(a))
#define long long long

const int N = 504;

using namespace std;
int a[N][N];
char s[N];
int n, m;
int h[N], L[N], R[N];
long memo[5][5][5];

long cal(int c1, int c2, int c3) {
    long &ret = memo[c1][c2][c3];
    if (ret >= 0) return ret;
    ret = 0;
    REP(j, 1, n) h[j] = 0;
    REP(i, 1, m) {
        REP(j, 1, n)
        if (a[i][j] == c1 || a[i][j] == c2 || a[i][j] == c3)
            ++h[j]; else h[j] = 0;
        REP(j, 1, n)
            for(L[j] = j - 1; L[j] > 0 && h[L[j]] >= h[j]; L[j] = L[L[j]]);
        REPD(j, n, 1)
            for(R[j] = j + 1; R[j] <= n && h[R[j]] > h[j]; R[j] = R[R[j]]);
        REP(j, 1, n)
        if (h[j])
            ret += (long)(j - L[j]) * (R[j] - j) * h[j];
    }
    return ret;
}

int main() {
    #ifdef _LAD_
        freopen("CRECT.inp", "r", stdin);
    #endif // _LAD_
    scanf("%d %d\n", &m, &n);
    REP(i, 1, m) {
        scanf("%s\n", s + 1);
        REP(j, 1, n)
            a[i][j] = s[j] - 'A';
    }
    RESET(memo, -1);
    long ans = 0;
    FOR(i, 0, 5) FOR(j, 0, i) FOR(k, 0, j) {
        ans += cal(i, i, i) + cal(j, j, j) + cal(k, k, k)
             - cal(i, j, j) - cal(i, k, k) - cal(j, k, k)
             + cal(i, j, k);
    }
    cout << ans << endl;
    return 0;
}
