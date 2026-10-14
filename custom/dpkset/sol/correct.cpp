#include <algorithm>
#include <cstdio>
#include <vector>

constexpr int MOD = 1000000007;
constexpr long long NEG = -(1LL << 60);
struct State {
    long long value = NEG;
    int ways = 0;
};
void relax(State &dest, long long value, int ways) {
    if (value > dest.value) dest = {value, ways};
    else if (value == dest.value) {
        dest.ways += ways;
        if (dest.ways >= MOD) dest.ways -= MOD;
    }
}
int main() {
    if (fopen("cau3.inp", "r")) freopen("cau3.inp", "r", stdin), freopen("cau3.out", "w", stdout);
    int n, k;
    if (scanf("%d%d", &n, &k) != 2) return 0;
    std::vector<int> a(k);
    for (int &v : a) scanf("%d", &v);
    std::vector<State> keep(k), drop(k);
    keep[0] = {0, 1};
    // drop[j]: j chosen positions; a deletion among the first j coefficients,
    // with coefficient j+1 already matched. Deleting the last coefficient
    // is accounted for only once, after scanning the entire sequence.
    for (int i = 0; i < n; ++i) {
        long long x; scanf("%lld", &x);
        for (int j = std::min(k-1, i+1); j >= 1; --j) {
            if (drop[j-1].value != NEG)
                relax(drop[j], drop[j-1].value + a[j]*x, drop[j-1].ways);
            if (keep[j-1].value != NEG) {
                // Delete coefficient j, then match coefficient j+1 to x.
                relax(drop[j], keep[j-1].value + a[j]*x, keep[j-1].ways);
                relax(keep[j], keep[j-1].value + a[j-1]*x, keep[j-1].ways);
            }
        }
    }
    State ans = keep[k-1]; // Delete coefficient k.
    if (drop[k-1].value != NEG) relax(ans, drop[k-1].value, drop[k-1].ways);
    printf("%lld %d\n", ans.value, ans.ways);
}
