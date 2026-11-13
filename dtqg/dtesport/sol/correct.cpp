#include <bits/stdc++.h>
using namespace std;

struct Run {
    long long first = 0, last = 0;
    long long firstDiff = 0, lastDiff = 0;
    int length = 0, prefix = 0, suffix = 0, best = 0;
};

Run mergeRuns(const Run& a, const Run& b) {
    long long bridge = b.first - a.last;
    int left = bridge == a.lastDiff ? a.suffix : 1;
    int right = bridge == b.firstDiff ? b.prefix : 1;
    return {
        a.first, b.last,
        a.length == 1 ? bridge : a.firstDiff,
        b.length == 1 ? bridge : b.lastDiff,
        a.length + b.length,
        left == a.length ? a.length + right : a.prefix,
        right == b.length ? b.length + left : b.suffix,
        max(max(a.best, b.best), left + right)
    };
}

struct Change {
    // At index i, apply intercept + i * slope.
    long long intercept = 0, slope = 0;
    bool assign = false;
};

class SegmentTree {
    struct Node {
        Run run;
        Change pending;
    };

    vector<Node> tree;
    int size;

    void build(int p, int lo, int hi, const vector<int>& values) {
        if (lo == hi) {
            tree[p].run = {values[lo], values[lo], 0, 0, 1, 1, 1, 1};
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * p, lo, mid, values);
        build(2 * p + 1, mid + 1, hi, values);
        pull(p);
    }

    void pull(int p) {
        tree[p].run = mergeRuns(tree[2 * p].run, tree[2 * p + 1].run);
    }

    void apply(int p, int lo, int hi, const Change& change) {
        auto& [run, pending] = tree[p];
        long long first = change.intercept + lo * change.slope;
        long long last = change.intercept + hi * change.slope;
        if (change.assign) {
            run = {first, last, change.slope, change.slope,
                   run.length, run.length, run.length, run.length};
            pending = change;
        } else {
            run.first += first;
            run.last += last;
            run.firstDiff += change.slope;
            run.lastDiff += change.slope;
            pending.intercept += change.intercept;
            pending.slope += change.slope;
        }
    }

    void push(int p, int lo, int mid, int hi) {
        auto& change = tree[p].pending;
        if (change.assign || change.intercept != 0 || change.slope != 0) {
            apply(2 * p, lo, mid, change);
            apply(2 * p + 1, mid + 1, hi, change);
            change = {};
        }
    }

    void update(int p, int lo, int hi, int l, int r, const Change& change) {
        if (l <= lo && hi <= r) {
            apply(p, lo, hi, change);
            return;
        }
        int mid = (lo + hi) / 2;
        push(p, lo, mid, hi);
        if (l <= mid) update(2 * p, lo, mid, l, r, change);
        if (r > mid) update(2 * p + 1, mid + 1, hi, l, r, change);
        pull(p);
    }

    Run query(int p, int lo, int hi, int l, int r) {
        if (l <= lo && hi <= r) return tree[p].run;
        int mid = (lo + hi) / 2;
        push(p, lo, mid, hi);
        if (r <= mid) return query(2 * p, lo, mid, l, r);
        if (l > mid) return query(2 * p + 1, mid + 1, hi, l, r);
        return mergeRuns(query(2 * p, lo, mid, l, r),
                         query(2 * p + 1, mid + 1, hi, l, r));
    }

public:
    explicit SegmentTree(const vector<int>& values)
        : tree(4 * values.size()), size(static_cast<int>(values.size())) {
        build(1, 0, size - 1, values);
    }

    void update(int l, int r, long long start, long long slope, bool assign) {
        update(1, 0, size - 1, l, r, {start - l * slope, slope, assign});
    }

    int longest(int l, int r) {
        return query(1, 0, size - 1, l, r).best;
    }
};

int main() {
    if (FILE* input = fopen("ESPORT.INP", "r")) {
        fclose(input);
        freopen("ESPORT.INP", "r", stdin);
        freopen("ESPORT.OUT", "w", stdout);
    }
    int n, q; cin >> n >> q;
    vector<int> values(n);
    for (auto& value : values) cin >> value;
    SegmentTree tree(values);
    while (q--) {
        int type, l, r; cin >> type >> l >> r;
        l--, r--;
        if (type == 3) {
            printf("%d\n", tree.longest(l, r));
        } else {
            int s, c; cin >> s >> c;
            tree.update(l, r, s, c, type == 2);
        }
    }
}
