#include <cstdio>
#include <map>
#include <vector>
using namespace std;
using ll = long long;

ll lookup(const map<ll, ll> &frequency, ll key) {
    auto it = frequency.find(key);
    return it == frequency.end() ? 0 : it->second;
}

int main() {
    int n;
    ll target;
    if (scanf("%d%lld", &n, &target) != 2) return 0;
    map<ll,ll> frequency;
    frequency[0] = 1;
    ll total = 0, answer = 0;
    for (int r = 1; r <= n; ++r) {
        ll x; if (scanf("%lld", &x) != 1) return 0;
        total += x;
        answer += lookup(frequency, total - target);
        ++frequency[total];
    }
    printf("%lld\n", answer);
}
