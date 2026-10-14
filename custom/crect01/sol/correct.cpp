#include <iostream>
#include <utility>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m,n;
    cin >> m >> n;
    vector<int> height(n,0);
    long long answer=0;
    for (int i=0; i<m; ++i) {
        vector<pair<int,int>> st;
        long long sum=0;
        for (int j=0; j<n; ++j) {
            int x; cin >> x;
            height[j]=x ? height[j]+1 : 0;
            int count=1;
            while (!st.empty() && st.back().first>=height[j]) {
                sum-=1LL*st.back().first*st.back().second;
                count+=st.back().second;
                st.pop_back();
            }
            st.emplace_back(height[j],count);
            sum+=1LL*height[j]*count;
            answer+=sum;
        }
    }
    cout << answer << '\n';
}
