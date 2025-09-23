/*
Author: Tu Pham Anh
Date: 2025/08/20 - 09:12
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int sum, l, r;
};

vector<Node> seg;
vector<int> root;

int addNode(int sum = 0, int l = 0, int r = 0) {
    seg.push_back({sum, l, r});
    return (int) seg.size() - 1;
}

int update(int prev, int l, int r, int pos) {
    int u = addNode(seg[prev].sum + 1, seg[prev].l, seg[prev].r);
    if (l == r) return u;
    int mid = (l + r) >> 1;
    if (pos <= mid) seg[u].l = update(seg[prev].l, l, mid, pos);
    else            seg[u].r = update(seg[prev].r, mid + 1, r, pos); 
    return u;
}

// Find k-th value in [tL + 1, tR]
int kth(int tL, int tR, int L, int R, int k) {
    if (L == R) return L;
    int mid = (L + R) >> 1;
    int sumLeft = seg[seg[tR].l].sum - seg[seg[tL].l].sum;
    if (sumLeft >= k) return kth(seg[tL].l, seg[tR].l, L, mid, k);
    return kth(seg[tL].r, seg[tR].r, mid + 1, R, k - sumLeft);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<int> a(n), num;
    for (auto &x: a) cin >> x, num.push_back(x); // Ensure values are within bounds
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());

    // seg.clear();
    // seg.reserve(n * (1 + (int)ceil(log2(n))) + 10); // Reserve space for segment tree
    root.push_back(addNode()); // Initial root for the first version
    int m = num.size();
    for (int i = 0; i < n; ++i) {
        a[i] = int(lower_bound(num.begin(), num.end(), a[i]) - num.begin()) + 1; // 1-based index
        int newRoot = update(root[i], 1, m, a[i]);
        root.push_back(newRoot);
    }

    while (q--) {
        int l, r, k;
        cin >> l >> r;
        k = (r - l) / 2 + 1; // Median position
        int result = kth(root[l - 1], root[r], 1, m, k);
        cout << num[result - 1] << '\n';
    }

    return 0;
}