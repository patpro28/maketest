#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
struct RangeFenwick {
    int n;
    vector<ll> slope, intercept;
    explicit RangeFenwick(int size) : n(size), slope(n + 2), intercept(n + 2) {}
    void point(vector<ll>& bit, int p, ll x) {
        for (; p <= n; p += p & -p) bit[p] += x;
    }
    ll get(const vector<ll>& bit, int p) const {
        ll result = 0;
        for (; p; p -= p & -p) result += bit[p];
        return result;
    }
    void add(int l, int r, ll x) {
        if (!x) return;
        point(slope, l, x); point(slope, r + 1, -x);
        point(intercept, l, x * (l - 1)); point(intercept, r + 1, -x * r);
    }
    ll prefix(int p) const { return p * get(slope, p) - get(intercept, p); }
    ll sum(int l, int r) const { return prefix(r) - prefix(l - 1); }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<ll> a(n + 1), answer(q);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<vector<pair<int, int>>> queries(n + 1);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r; queries[r].push_back({l, i});
    }
    RangeFenwick coefficient(n), constant(n);
    vector<int> stack;
    for (int r = 1; r <= n; ++r) {
        while (!stack.empty() && a[stack.back()] >= a[r]) {
            int p = stack.back(); stack.pop_back();
            int left = stack.empty() ? 1 : stack.back() + 1;
            coefficient.add(left, p, a[r] - a[p]);
            constant.add(left, p, (a[p] - a[r]) * (r - 1));
        }
        stack.push_back(r);
        coefficient.add(r, r, a[r]); constant.add(r, r, a[r] * (1 - r));
        for (auto [l, id] : queries[r]) answer[id] = r * coefficient.sum(l, r) + constant.sum(l, r);
    }
    for (ll value : answer) cout << value << '\n';
}
