#include <bits/stdc++.h>

using namespace std;

#define _int64 long long
#define mo 998244353

vector<int> a[210000];
int p[210000];
_int64 ans[210000];
int mi[210000];
int ma[210000];
int mi1[210000];
int ma1[210000];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int i, j, n, l, t, x, y, o, ss;
    _int64 tmp;
    vector<int> q;
    cin >> t;
    for (l = 0; l < t; l++)
    {
        cin >> n >> ss;
        ss--;
        for (i = 0; i < n; i++)
        {
            a[i].clear();
            p[i] = -1;
        }
        for (i = 0; i + 1 < n; i++)
        {
            cin >> x >> y;
            x--;
            y--;
            a[x].push_back(y);
            a[y].push_back(x);
        }
        q.clear();
        q.push_back(ss);
        ans[ss] = 0;
        mi[ss] = ss + 1;
        ma[ss] = ss + 1;
        for (i = 0; i < (int)q.size(); i++)
        {
            x = q[i];
            for (j = 0; j < (int)a[x].size(); j++)
            {
                y = a[x][j];
                if (y == p[x])
                    continue;
                q.push_back(y);
                p[y] = x;
                mi[y] = min(mi[x], y + 1);
                ma[y] = max(ma[x], y + 1);
                ans[y] = (_int64)mi[y] * ma[y];
            }
        }
        for (o = 0; o < ss; o++)
        {
            if ((o + 1) * (ss + 1) >= n * 2)
                break;
            tmp = (_int64)ma[o] * mi[o];
            for (i = 0; i < n; i++)
                p[i] = -1;
            q.clear();
            q.push_back(o);
            ma1[o] = o + 1;
            mi1[o] = o + 1;
            for (i = 0; i < (int) q.size(); i++)
            {
                x = q[i];
                for (j = 0; j < (int) a[x].size(); j++)
                {
                    y = a[x][j];
                    if (y == p[x])
                        continue;
                    p[y] = x;
                    q.push_back(y);
                    mi1[y] = min(mi1[x], y + 1);
                    ma1[y] = max(ma1[x], y + 1);
                    ans[y] = min(ans[y], tmp + (_int64)mi1[y] * ma1[y]);
                }
            }
        }
        for (i = 0; i < n; i++)
            cout << ans[i] << ' ';
        cout << '\n';
    }
}