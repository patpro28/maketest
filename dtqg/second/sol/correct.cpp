#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

pair<vector<int>, vector<int>> greater_right(const vector<int>& a) {
    int n = int(a.size());
    vector<int> first(n, n), second(n, n);
    stack<int> one, two, moved;
    for (int i = 0; i < n; ++i) {
        while (!two.empty() && a[two.top()] < a[i]) {
            int u = two.top(); two.pop();
            second[u] = i; 
        }
        while (!one.empty() && a[one.top()] < a[i]) {
            int u = one.top(); one.pop(); 
            first[u] = i; moved.push(u);
        }
        while (!moved.empty()) {
            two.push(moved.top()); moved.pop();
        }
        one.push(i);
    }
    return {first, second};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    auto [r1, r2] = greater_right(a);
    auto reversed = a; reverse(reversed.begin(), reversed.end());
    auto [b1, b2] = greater_right(reversed);
    ll answer = 0;
    for (int i = 0; i < n; ++i) {
        int l1 = n - 1 - b1[n - 1 - i], l2 = n - 1 - b2[n - 1 - i];
        ll ways = 1LL * (l1 - l2) * (r1[i] - i) + 1LL * (i - l1) * (r2[i] - r1[i]);
        answer += ways * a[i];
    }
    cout << answer << '\n';
}
