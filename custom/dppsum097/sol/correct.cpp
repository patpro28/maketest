#include <cstdio>
#include <map>
#include <vector>
using namespace std;
using ll = long long;


int main() {
    int n;
    int divisor;
    if (scanf("%d%d", &n, &divisor) != 2) return 0;
    vector<ll> frequency(divisor);
    frequency[0] = 1;
    ll total = 0, answer = 0;
    for (int r = 1; r <= n; ++r) {
        ll x; if (scanf("%lld", &x) != 1) return 0;
        total += x;
        int current = static_cast<int>((total % divisor + divisor) % divisor);
        int wanted = current;
        answer += frequency[wanted];
        ++frequency[current];
    }
    printf("%lld\n", answer);
}
