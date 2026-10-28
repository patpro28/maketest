#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

// Positive jumps of the derivative, ordered by their coordinates.
struct JumpTreap {
    struct Node {
        int left = 0, right = 0;
        uint64_t priority = 0;
        ll x = 0, weight = 0, mass = 0, moment = 0;
    };
    vector<Node> t{Node{}};
    uint64_t random_state = 0x6492c5ab317d8e01ULL;
    explicit JumpTreap(int n) { t.reserve(3 * n + 5); }
    ll mass(int u) const { return t[u].mass; }
    ll moment(int u) const { return t[u].moment; }
    void pull(int u) {
        t[u].mass = mass(t[u].left) + t[u].weight + mass(t[u].right);
        t[u].moment = moment(t[u].left) + t[u].x * t[u].weight + moment(t[u].right);
    }
    int node(ll x, ll weight) {
        random_state ^= random_state << 7; random_state ^= random_state >> 9;
        Node a; a.x = x; a.weight = a.mass = weight; a.moment = x * weight; a.priority = random_state;
        t.push_back(a); return int(t.size()) - 1;
    }
    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (t[a].priority > t[b].priority) {
            t[a].right = merge(t[a].right, b); pull(a); return a;
        }
        t[b].left = merge(a, t[b].left); pull(b); return b;
    }
    pair<int, int> split_key(int u, ll x) {
        if (!u) return {0, 0};
        if (t[u].x <= x) {
            auto [a, b] = split_key(t[u].right, x);
            t[u].right = a; pull(u); return {u, b};
        }
        auto [a, b] = split_key(t[u].left, x);
        t[u].left = b; pull(u); return {a, u};
    }
    pair<int, int> split_mass(int u, ll count) {
        if (!u || count == 0) return {0, u};
        if (count >= mass(u)) return {u, 0};
        ll before = mass(t[u].left);
        if (count < before) {
            auto [a, b] = split_mass(t[u].left, count);
            t[u].left = b; pull(u); return {a, u};
        }
        if (count > before + t[u].weight) {
            auto [a, b] = split_mass(t[u].right, count - before - t[u].weight);
            t[u].right = a; pull(u); return {u, b};
        }
        if (count == before) { int a = t[u].left; t[u].left = 0; pull(u); return {a, u}; }
        if (count == before + t[u].weight) { int b = t[u].right; t[u].right = 0; pull(u); return {u, b}; }
        ll used = count - before, rest = t[u].weight - used;
        int old_right = t[u].right;
        t[u].right = 0; t[u].weight = used; pull(u);
        int b = node(t[u].x, rest);
        return {u, merge(b, old_right)};
    }
    int insert(int root, ll x, ll weight) {
        auto [a, bc] = split_key(root, x - 1);
        auto [b, c] = split_key(bc, x);
        int middle = node(x, mass(b) + weight);
        return merge(merge(a, middle), c);
    }
    ll kth(int u, ll rank) const {
        while (true) {
            ll before = mass(t[u].left);
            if (rank <= before) u = t[u].left;
            else if (rank <= before + t[u].weight) return t[u].x;
            else { rank -= before + t[u].weight; u = t[u].right; }
        }
    }
    pair<ll, ll> prefix(int u, ll x) const {
        ll sum = 0, total = 0;
        while (u) {
            if (t[u].x > x) u = t[u].left;
            else {
                sum += mass(t[u].left) + t[u].weight;
                total += moment(t[u].left) + t[u].x * t[u].weight;
                u = t[u].right;
            }
        }
        return {sum, total};
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> a(n), w(n), c(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> w[i];
    for (int i = 0; i + 1 < n; ++i) cin >> c[i];
    JumpTreap tree(n);
    int root = 0;
    ll slope = 0, intercept = 0;
    for (int i = 0; i < n; ++i) {
        if (i && slope > c[i - 1]) {
            ll removed = slope - c[i - 1];
            auto [left, rest] = tree.split_mass(root, removed);
            auto [middle, right] = tree.split_mass(rest, 2 * c[i - 1]);
            (void)right;
            intercept -= tree.moment(left);
            root = middle; slope = c[i - 1];
        }
        intercept += w[i] * a[i]; slope += w[i];
        root = tree.insert(root, a[i], 2 * w[i]);
    }
    ll x = tree.kth(root, slope);
    auto [mass, moment] = tree.prefix(root, x);
    cout << intercept - slope * x + mass * x - moment << '\n';
}
