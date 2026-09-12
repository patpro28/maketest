#include <bits/stdc++.h>
using namespace std;

#define Rep(i, n) for (int i = 0; i < n; ++i)
using akt = int;
using vi = vector<int>;

int main()
{
    // your code goes here
    akt t;
    cin >> t;
    while (t--)
    {
        akt n;
        cin >> n;
        vi arr(n + 1, 0);
        Rep(i, n + 1)
                cin >>
            arr[i];
        akt ans = std::numeric_limits<int>::max();
        Rep(i, n)
            ans = fmin(ans, fmax(arr[i], arr[i + 1]));
        cout << ans << endl;
    }
}
