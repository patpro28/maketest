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
    ll target; int lower, upper;
    if (scanf("%d%lld%d%d", &n, &target, &lower, &upper) != 4) return 0;
    vector<ll> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll x; if (scanf("%lld", &x) != 1) return 0;
        prefix[i] = prefix[i-1] + x;
    }
    map<ll,ll> frequency;
    ll answer = 0;
    for (int r = 1; r <= n; ++r) {
        if (r >= lower) ++frequency[prefix[r-lower]];
        if (r-upper-1 >= 0) remove_one(frequency, prefix[r-upper-1]);
        answer += lookup(frequency, prefix[r] - target);
    }
    printf("%lld\n", answer);
}
