#include <bits/stdc++.h>
#define int long long int
using namespace std;

int f(int n)
{
  int cur = 0, ans = n;
  int cnt = 0;
  while (n % 2 == 0)
  {
    n /= 2;
    cnt++;
  }
  if (cnt > cur)
  {
    ans = 2;
    cur = cnt;
  }
  for (int i = 3; i * i <= n; i += 2)
  {
    cnt = 0;
    while (n % i == 0)
    {
      n /= i;
      cnt++;
    }
    if (cnt > cur)
    {
      ans = i;
      cur = cnt;
    }
  }
  if (n > 1)
  {
    if (1 > cur)
    {
      ans = n;
      cur = 1;
    }
  }
  return ans;
}
void myfun()
{
  int n;
  cin >> n;
  cout << f(n) << "\n";
}

signed main()
{
  int t = 1;
  cin >> t;
  for (int tt = 1; tt <= t; tt++)
  {
    myfun();
  }
  return 0;
}