// Independent O(n*k*k) solution: enumerate the deleted position.
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
    int n,k; scanf("%d%d", &n, &k);
    std::vector<long long> a(k),x(n);
    for (auto &v:a) scanf("%lld", &v);
    for (auto &v:x) scanf("%lld", &v);
    constexpr long long NEG = -(1LL << 60);
    constexpr int MOD = 1000000007;
    long long best = NEG;
    int count = 0;
    for (int deleted = 0; deleted < k; ++deleted) {
        std::vector<long long> b;
        for (int i = 0; i < k; ++i) if (i != deleted) b.push_back(a[i]);
        std::vector<long long> value(k,NEG);
        std::vector<int> ways(k,0);
        value[0]=0; ways[0]=1;
        for (long long v:x) for (int j=k-1; j>=1; --j) if (value[j-1] != NEG) {
            long long candidate = value[j-1] + b[j-1]*v;
            if (candidate > value[j]) { value[j]=candidate; ways[j]=ways[j-1]; }
            else if (candidate == value[j]) ways[j]=(ways[j]+ways[j-1])%MOD;
        }
        if (value[k-1] > best) { best=value[k-1]; count=ways[k-1]; }
        else if (value[k-1] == best) count=(count+ways[k-1])%MOD;
    }
    printf("%lld %d\n",best,count);
}
