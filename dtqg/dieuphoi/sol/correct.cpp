#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> a(n), length(n), gap(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> length[i];
    for (int i = 0; i + 1 < n; ++i) cin >> gap[i];
    priority_queue<ll> heap;
    ll shift = 0, answer = 0;
    for (int i = 0; i < n; ++i) {
        if (i) shift += length[i - 1] + gap[i - 1];
        ll target = a[i] - shift;
        heap.push(target);
        if (heap.top() > target) {
            answer += heap.top() - target;
            heap.pop(); heap.push(target);
        }
    }
    cout << answer << '\n';
}
