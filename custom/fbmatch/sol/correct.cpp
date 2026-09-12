#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    string s;
    cin >> n >> s;
    vector<int> arr(26, 0);
    for (auto &ch : s)
    {
        arr[ch - 'a']++;
    }
    for (int i = 0; i < 26; ++i)
    {
        if (arr[i] >= 2)
        {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}
int main()
{
    // your code goes here
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
