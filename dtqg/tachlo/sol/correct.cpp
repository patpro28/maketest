#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 4000000000000000000LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, groups;
    cin >> n >> groups;
    vector<int> a(n + 1), frequency(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<ll> previous(n + 1, INF), current(n + 1, INF);
    previous[0] = 0;
    for (int layer = 1; layer <= groups; ++layer) {
        fill(current.begin(), current.end(), INF);
        fill(frequency.begin(), frequency.end(), 0);
        int left = 1, right = 0;
        ll cost = 0;
        auto add = [&](int pos) { cost += frequency[a[pos]]++; };
        auto remove = [&](int pos) { cost -= --frequency[a[pos]]; };
        auto interval_cost = [&](int l, int r) {
            while (left > l) add(--left);
            while (right < r) add(++right);
            while (left < l) remove(left++);
            while (right > r) remove(right--);
            return cost;
        };
        auto divide = [&](auto&& self, int l, int r, int opt_l, int opt_r) -> void {
            if (l > r) return;
            int mid = (l + r) / 2, best_cut = -1;
            for (int cut = opt_l; cut <= min(mid - 1, opt_r); ++cut) {
                ll value = interval_cost(cut + 1, mid);
                if (previous[cut] == INF) continue;
                value += previous[cut];
                if (value < current[mid]) { current[mid] = value; best_cut = cut; }
            }
            self(self, l, mid - 1, opt_l, best_cut);
            self(self, mid + 1, r, best_cut, opt_r);
        };
        divide(divide, layer, n, layer - 1, n - 1);
        previous.swap(current);
    }
    cout << previous[n] << '\n';
}
