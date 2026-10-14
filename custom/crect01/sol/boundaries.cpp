#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m,n; cin >> m >> n;
    vector<int> h(n),left(n),right(n),st;
    long long answer=0;
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            int x; cin >> x;
            h[j]=x ? h[j]+1 : 0;
        }
        st.clear();
        for (int j=0; j<n; ++j) {
            while (!st.empty() && h[st.back()]>=h[j]) st.pop_back();
            left[j]=st.empty() ? -1 : st.back();
            st.push_back(j);
        }
        st.clear();
        for (int j=n-1; j>=0; --j) {
            while (!st.empty() && h[st.back()]>h[j]) st.pop_back();
            right[j]=st.empty() ? n : st.back();
            st.push_back(j);
        }
        for (int j=0; j<n; ++j)
            answer+=1LL*h[j]*(j-left[j])*(right[j]-j);
    }
    cout << answer << '\n';
}
