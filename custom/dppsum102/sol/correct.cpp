#include <algorithm>
#include <climits>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

long long s[200005], x;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    s[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        s[i] = s[i - 1] + x;
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        if (s[i - 1] == s[n] - s[i])
            ans.push_back(i);
    }
    cout << ans.size() << "\n";
    for (int i : ans)
        cout << i << " ";
    cout << "\n";
}
