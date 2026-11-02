#include <cstdio>
#include <map>
#include <vector>
using namespace std;
using ll = long long;

ll lookup(const map<ll, ll> &frequency, ll key) {
    auto it = frequency.find(key);
    return it == frequency.end() ? 0 : it->second;
}
void remove_one(map<ll, ll> &frequency, ll key) {
    auto it = frequency.find(key);
    if (--it->second == 0) frequency.erase(it);
}

int main() {
    int n;
    ll target; int k;
    if (scanf("%d%lld%d", &n, &target, &k) != 3) return 0;
    vector<ll> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll x; if (scanf("%lld", &x) != 1) return 0;
        prefix[i] = prefix[i-1] + x;
    }
    map<ll,ll> frequency;
    ll answer = 0;
    frequency[0] = 1;
    for (int r = 1; r <= n; ++r) {
        if (r-k-1 >= 0) remove_one(frequency, prefix[r-k-1]);
        answer += lookup(frequency, prefix[r] - target);
        ++frequency[prefix[r]];
    }
    printf("%lld\n", answer);
}
