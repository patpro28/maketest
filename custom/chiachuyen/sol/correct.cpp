#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 4000000000000000000LL;

struct SegmentTree {
    int n;
    vector<ll> mn, lazy;
    explicit SegmentTree(int size) : n(size), mn(4 * size, INF), lazy(4 * size) {}
    void apply(int v, ll x) { mn[v] += x; lazy[v] += x; }
    void push(int v) {
        if (lazy[v]) {
            apply(v * 2, lazy[v]);
            apply(v * 2 + 1, lazy[v]);
            lazy[v] = 0;
        }
    }
    void set_value(int v, int l, int r, int pos, ll x) {
        if (l == r) { mn[v] = x; lazy[v] = 0; return; }
        push(v);
        int mid = (l + r) / 2;
        if (pos <= mid) set_value(v * 2, l, mid, pos, x);
        else set_value(v * 2 + 1, mid + 1, r, pos, x);
        mn[v] = min(mn[v * 2], mn[v * 2 + 1]);
    }
    void add(int v, int l, int r, int ql, int qr, ll x) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) { apply(v, x); return; }
        push(v);
        int mid = (l + r) / 2;
        add(v * 2, l, mid, ql, qr, x);
        add(v * 2 + 1, mid + 1, r, ql, qr, x);
        mn[v] = min(mn[v * 2], mn[v * 2 + 1]);
    }
    ll query(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return INF;
        if (ql <= l && r <= qr) return mn[v];
        push(v);
        int mid = (l + r) / 2;
        return min(query(v * 2, l, mid, ql, qr),
                   query(v * 2 + 1, mid + 1, r, ql, qr));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, lower, upper;
    ll c;
    cin >> n >> lower >> upper >> c;
    vector<ll> h(n + 1), dp(n + 1, INF);
    for (int i = 1; i <= n; ++i) cin >> h[i];
    dp[0] = 0;
    SegmentTree tree(n);
    vector<int> max_stack, min_stack;
    for (int i = 1; i <= n; ++i) {
        // Leaf j stores dp[j] + max(h[j+1..i]) - min(h[j+1..i]).
        tree.set_value(1, 0, n - 1, i - 1, dp[i - 1]);
        while (!max_stack.empty() && h[max_stack.back()] <= h[i]) {
            int pos = max_stack.back();
            max_stack.pop_back();
            int left = max_stack.empty() ? 0 : max_stack.back();
            tree.add(1, 0, n - 1, left, pos - 1, h[i] - h[pos]);
        }
        max_stack.push_back(i);
        while (!min_stack.empty() && h[min_stack.back()] >= h[i]) {
            int pos = min_stack.back();
            min_stack.pop_back();
            int left = min_stack.empty() ? 0 : min_stack.back();
            tree.add(1, 0, n - 1, left, pos - 1, h[pos] - h[i]);
        }
        min_stack.push_back(i);
        if (i >= lower) {
            ll best = tree.query(1, 0, n - 1, max(0, i - upper), i - lower);
            if (best < INF / 2) dp[i] = best + c;
        }
    }
    cout << (dp[n] == INF ? -1 : dp[n]) << '\n';
}
