#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct SegTree
{
    int n;
    vector<int> st;

    SegTree(int sz)
    {
        n = 1;
        while (n < sz)
            n <<= 1;
        st.assign(2 * n, INF);
    }

    void update(int pos, int val)
    {
        pos += n;
        st[pos] = val;

        for (pos >>= 1; pos; pos >>= 1)
        {
            st[pos] = min(st[pos << 1], st[pos << 1 | 1]);
        }
    }

    int query(int l, int r)
    {
        if (l > r)
            return INF;

        l += n;
        r += n;

        int res = INF;

        while (l <= r)
        {
            if (l & 1)
                res = min(res, st[l++]);
            if (!(r & 1))
                res = min(res, st[r--]);

            l >>= 1;
            r >>= 1;
        }

        return res;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> D(N + 1);

    for (int i = 1; i <= N; i++)
    {
        cin >> D[i];
    }

    // coordinate compression
    vector<int> vals;

    for (int i = 1; i <= N; i++)
    {
        vals.push_back(D[i]);
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    int M = vals.size();

    auto getId = [&](int x)
    {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    };

    vector<int> id(N + 1);

    for (int i = 1; i <= N; i++)
    {
        id[i] = getId(D[i]);
    }

    vector<int> dp(N + 1, INF);
    dp[1] = 0;

    // multiset lưu các dp active theo độ cao
    vector<multiset<int>> box(M);

    SegTree seg(M);

    auto rebuild = [&](int p)
    {
        int val = INF;

        if (!box[p].empty())
        {
            val = *box[p].begin();
        }

        seg.update(p, val);
    };

    auto add = [&](int idx)
    {
        int p = id[idx];

        box[p].insert(dp[idx]);

        rebuild(p);
    };

    auto removePos = [&](int idx)
    {
        int p = id[idx];

        box[p].erase(box[p].find(dp[idx]));

        rebuild(p);
    };

    add(1);

    for (int i = 2; i <= N; i++)
    {

        int old = i - K - 1;

        if (old >= 1)
        {
            removePos(old);
        }

        int p = id[i];

        int bestGreater = seg.query(p + 1, M - 1);

        int bestSmaller = seg.query(0, p);

        dp[i] = min(bestGreater, bestSmaller + 1);

        add(i);
    }

    cout << dp[N] << '\n';
}