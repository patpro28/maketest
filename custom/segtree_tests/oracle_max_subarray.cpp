// Independent reference: offline divide-and-conquer with forward/backward Kadane scans.
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
using i64 = long long;
struct Query { int l, r; };
class Reference {
    std::vector<i64> a, left_best, right_best, left_suffix, right_prefix;
    std::vector<Query> queries;
    std::vector<i64> answers;
    void solve(int l, int r, const std::vector<int> &ids) {
        if (ids.empty()) return;
        if (l == r) { for (int id : ids) answers[id] = a[l]; return; }
        int mid = (l+r)/2;
        i64 running = 0, sum = 0, best = std::numeric_limits<i64>::lowest();
        i64 boundary = best;
        for (int i=mid; i>=l; --i) {
            running = i == mid ? a[i] : std::max(a[i],a[i]+running);
            best = std::max(best,running); left_best[i] = best;
            sum += a[i]; boundary = std::max(boundary,sum); left_suffix[i] = boundary;
        }
        running = 0; sum = 0; best = std::numeric_limits<i64>::lowest(); boundary = best;
        for (int i=mid+1; i<=r; ++i) {
            running = i == mid+1 ? a[i] : std::max(a[i],a[i]+running);
            best = std::max(best,running); right_best[i] = best;
            sum += a[i]; boundary = std::max(boundary,sum); right_prefix[i] = boundary;
        }
        std::vector<int> first, second;
        for (int id : ids) {
            int u=queries[id].l,v=queries[id].r;
            if (v<=mid) first.push_back(id);
            else if (u>mid) second.push_back(id);
            else answers[id] = std::max({left_best[u],right_best[v],left_suffix[u]+right_prefix[v]});
        }
        solve(l,mid,first); solve(mid+1,r,second);
    }
public:
    void run() {
        int n; std::cin >> n; a.resize(n);
        for (i64 &x : a) std::cin >> x;
        int m; std::cin >> m; queries.resize(m); answers.resize(m);
        for (Query &q : queries) { std::cin >> q.l >> q.r; --q.l; --q.r; }
        left_best.resize(n); right_best.resize(n); left_suffix.resize(n); right_prefix.resize(n);
        std::vector<int> ids(m); std::iota(ids.begin(),ids.end(),0); solve(0,n-1,ids);
        for (i64 x : answers) std::cout << x << '\n';
    }
};
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    Reference reference; reference.run();
}
