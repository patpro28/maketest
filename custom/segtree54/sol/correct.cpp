#include <bits/stdc++.h>
using namespace std;

vector<int> st, lz;
int _n;

void up(int k, int v) {
    st[k] = st[k] + v;
    lz[k] = lz[k] + v;
}

void push(int k, int z) {
    up(k + 1, lz[k]);
    up(z, lz[k]);
    lz[k] = 0;
}

void update(int tl, int tr, int l, int r, int v, int k = 1) {
    if (tl > r || l > tr)
        return;
    if (l <= tl and tr <= r) {
        up(k, v);
        return;
    }
    int mid = (tl + tr) >> 1;
    int z = k + (mid - tl + 1) * 2;
    push(k, z);
    update(tl, mid, l, r, v, k + 1);
    update(mid + 1, tr, l, r, v, z);
    st[k] = min(st[k + 1], st[z]);
}

int sum(int tl, int tr, int l, int r, int k = 1) {
    if (tl > r || l > tr)
        return 1e9;
    if (l <= tl and tr <= r)
        return st[k];
    int mid = (tl + tr) >> 1;
    int z = k + (mid - tl + 1) * 2;
    push(k, z);
    return min(sum(tl, mid, l, r, k + 1),
               sum(mid + 1, tr, l, r, z));
}

int sum(int l, int r) {
    return sum(0, _n - 1, l, r);
}

void update(int l, int r, int v) {
    update(0, _n - 1, l, r, v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    vector<int> dp(n + 1, -1), pre(n + 1, 1e9);
    pre[0] = 0;
    map<int, int> last;
    _n = n + 1;
    st.resize(_n << 1);
    lz.resize(_n << 1);

    for (int i = 1; i <= k; ++i) {
        fill(st.begin(), st.end(), 0);
        fill(lz.begin(), lz.end(), 0);
        last.clear();
        update(0, 0, pre[0]);
        dp[0] = 1e9;
        for (int j = 1; j <= n; ++j) {
            // Nếu đã xuất hiện trước đó thì mọi cost[k][j] với k < last[a[j]] đều sẽ tăng thêm j - last[a[j]]
            if (last.count(a[j]))
                update(0, last[a[j]] - 1, j - last[a[j]]);

            // Chỉ có j >= i mới chia được thành i đoạn
            dp[j] = j >= i ? sum(0, j - 1) : 1e9;

            // Cập nhật dp[j] vào segment tree (chưa có cost[k + 1][j])
            update(j, j, pre[j]);

            // Cập nhật last[a[j]] = j
            last[a[j]] = j;
        }
        swap(pre, dp);
    }

    cout << pre[n] << '\n';
    return 0;
}
