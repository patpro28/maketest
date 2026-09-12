// ladchat supremacy
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000000007
int main()
{
    ll t;
    cin >> t;

    while (t--)
    {
        ll n;
        cin >> n;
        string s, ans;
        cin >> ans;
        // string ans;
        cin >> s;
        vector<ll> need(n, 0);
        for (ll i = 0; i < n; i++)
            if (s[i] != ans[i])
                need[i]++;
        ll first, last;
        first = last = -1;
        for (ll i = 0; i < n; i++)
        {
            if (s[i] != ans[i])
            {
                first = i;
                break;
            }
        }
        for (ll i = n - 1; i >= 0; i--)
        {
            if (s[i] != ans[i])
            {
                last = i;
                break;
            }
        }

        ll seg = 0;
        ll it = 0;
        while (it < n)
        {
            if (s[it] != ans[it])
            {
                while (it < n && s[it] != ans[it])
                    it++;
                seg++;
            }
            else
                it++;
        }
        // cout<<first<<" "<<last<<" ";
        // cout<<seg<<" ";
        if (seg == 1)
        {

            ll fin = 0;
            fin = ((first - 0) + (n - 1 - last)) * 2 + (last - first) * 2; // first and last belong to same segment
            cout << fin << endl;
        }
        else if (seg == 0)
        {
            cout << (n * (n + 1) / 2) << endl;
        }
        else if (seg > 2)
            cout << 0 << endl;
        else
        {
            cout << 6 << endl;
        }
    }
    return 0;
}