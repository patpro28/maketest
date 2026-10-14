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
    int n; scanf("%d", &n); vector<int> t(n); int total=0;
    for (int &v:t) { scanf("%d", &v); total+=v; }
    int half=total/2; vector<char> dp(half+1,false); dp[0]=true;
    for (int v:t) for (int s=half; s>=v; --s) dp[s]=dp[s] || dp[s-v];
    for (int s=half; s>=0; --s) if(dp[s]) { printf("%d\n",total-s); break; }
}
