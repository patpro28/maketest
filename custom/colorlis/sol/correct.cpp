#include <bits/stdc++.h>
using namespace std;

// Find longest non-increasing subsequence
int longestNonIncreasingSubsequence(vector<int> &a)
{
    int n = a.size();
    vector<int> b;
    for (int i = 0; i < n; i++)
    {
        auto it = upper_bound(b.begin(), b.end(), a[i], greater<int>());
        if (it == b.end())
            b.push_back(a[i]);
        else
            *it = a[i];
    }
    return b.size();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    cout << longestNonIncreasingSubsequence(a) << '\n';
    return 0;
}
