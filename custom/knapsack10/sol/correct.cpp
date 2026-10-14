#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main() {
    int n; long long x; scanf("%d%lld", &n, &x);
    vector<int> a(n); int total=0;
    for (int &v:a) { scanf("%d", &v); total+=v; }
    if (x < -total || x > total || (total+x)%2 != 0) { puts("NO"); return 0; }
    int target=int((total+x)/2);
    vector<char> dp(target+1, false); dp[0]=true;
    for (int v:a) for (int s=target; s>=v; --s) dp[s]=dp[s] || dp[s-v];
    puts(dp[target] ? "YES" : "NO");
}
